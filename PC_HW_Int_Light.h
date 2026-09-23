#pragma once

#include <ModelCore/Platform.h>
#include <g3log/g3log.hpp>
#include "Header.h"

#include <array>
#include <algorithm>
#include <cstring>
#include <initializer_list>
#include <type_traits>

namespace Plugins
{
	namespace FlexCard3
	{
		namespace PC_HW_Interface
		{
			namespace Light
			{
				//======================================================================================
				// Forward declarations (BEFORE HwSerializer namespace)
				//======================================================================================

				class HwComDataInterface;

				template <size_t Size>
				class HwComDataBase;

				template <typename ValueType, size_t Size>
				class HwComDataObject;

				template <size_t Size>
				class HwComDataObject<void, Size>;

				//======================================================================================
				// Serializer helpers - merged from HwSerializer namespace
				//======================================================================================

				namespace HwSerializer
				{
					inline uint64_t myHtonll(uint64_t doubleBitRepresentation)
					{
						LOG(INFO) << "HwSerializer::myHtonll called";

						if (kIsLittleEndian)
						{
							uint32_t high_part_host_order = static_cast<uint32_t>(doubleBitRepresentation >> 32);
							uint32_t low_part_host_order = static_cast<uint32_t>(doubleBitRepresentation & 0xFFFFFFFFULL);
							uint64_t result = (static_cast<uint64_t>(htonl(low_part_host_order)) << 32) | htonl(high_part_host_order);
							LOG(INFO) << "HwSerializer::myHtonll little-endian conversion done";
							return result;
						}

						LOG(INFO) << "HwSerializer::myHtonll big-endian host, returning unchanged";
						return doubleBitRepresentation;
					}

					inline uint64_t myNtohll(uint64_t doubleBitRepresentation) noexcept
					{
						LOG(INFO) << "HwSerializer::myNtohll called";
						return myHtonll(doubleBitRepresentation);
					}

					struct DirectCopyPolicy
					{
						template <typename ValueType, size_t Size>
						static void toRaw(HwComDataObject<ValueType, Size>& data) noexcept
						{
							LOG(INFO) << "DirectCopyPolicy::toRaw called";
							std::memset(data.getRawData(), 0, Size);
							ValueType phys = data.getPhysical();
							std::memcpy(data.getRawData(), &phys, sizeof(ValueType));
							LOG(INFO) << "DirectCopyPolicy::toRaw completed";
						}

						template <typename ValueType, size_t Size>
						static void toPhysical(HwComDataObject<ValueType, Size>& data) noexcept
						{
							LOG(INFO) << "DirectCopyPolicy::toPhysical called";
							ValueType phys{};
							std::memcpy(&phys, data.getRawData(), sizeof(ValueType));
							data.setPhysical(phys);
							LOG(INFO) << "DirectCopyPolicy::toPhysical completed";
						}

						template <size_t Size>
						static void toRaw(HwComDataObject<void, Size>&) noexcept
						{
							LOG(INFO) << "DirectCopyPolicy::toRaw<void> called (no-op)";
						}

						template <size_t Size>
						static void toPhysical(HwComDataObject<void, Size>&) noexcept
						{
							LOG(INFO) << "DirectCopyPolicy::toPhysical<void> called (no-op)";
						}
					};

					struct SomeIpBigEndianPolicy
					{
						template <typename ValueType, size_t Size>
						static void toRaw(HwComDataObject<ValueType, Size>& data) noexcept
						{
							LOG(INFO) << "SomeIpBigEndianPolicy::toRaw called";
							std::memset(data.getRawData(), 0, Size);
							ValueType phys = data.getPhysical();

							if constexpr (sizeof(ValueType) == 1)
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toRaw 1-byte path";
								std::memcpy(data.getRawData(), &phys, 1);
							}
							else if constexpr (sizeof(ValueType) == 2)
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toRaw 2-byte path";
								uint16_t temp; std::memcpy(&temp, &phys, 2);
								uint16_t val = htons(temp);
								std::memcpy(data.getRawData(), &val, 2);
							}
							else if constexpr (sizeof(ValueType) == 4)
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toRaw 4-byte path";
								uint32_t temp; std::memcpy(&temp, &phys, 4);
								uint32_t val = htonl(temp);
								std::memcpy(data.getRawData(), &val, 4);
							}
							else if constexpr (sizeof(ValueType) == 8)
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toRaw 8-byte path";

								uint64_t temp; std::memcpy(&temp, &phys, 8);
								uint64_t val = myHtonll(temp);
								std::memcpy(data.getRawData(), &val, 8);

								/*LOG(INFO) << "SomeIpBigEndianPolicy::toRaw values:"
									<< " phys=" << static_cast<unsigned long long>(phys)
									<< " temp=" << static_cast<unsigned long long>(temp)
									<< " val=" << static_cast<unsigned long long>(val);*/

									// Enhanced logging showing both interpretations
								//LOG(INFO) << "SomeIpBigEndianPolicy::toRaw values (as double):" << " phys=" << std::fixed << std::setprecision(2) << static_cast<double>(phys);

								LOG(INFO) << "SomeIpBigEndianPolicy::toRaw values (as uint64_t):"
									<< " phys=" << static_cast<unsigned long long>(phys)
									<< " temp=" << static_cast<unsigned long long>(temp)
									<< " val=" << static_cast<unsigned long long>(val);

								LOG(INFO) << "SomeIpBigEndianPolicy::toRaw rawData[0..7]="
									<< static_cast<int>(data.getRawData()[0]) << " "
									<< static_cast<int>(data.getRawData()[1]) << " "
									<< static_cast<int>(data.getRawData()[2]) << " "
									<< static_cast<int>(data.getRawData()[3]) << " "
									<< static_cast<int>(data.getRawData()[4]) << " "
									<< static_cast<int>(data.getRawData()[5]) << " "
									<< static_cast<int>(data.getRawData()[6]) << " "
									<< static_cast<int>(data.getRawData()[7]);
							}
							else
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toRaw fallback path";
								std::memcpy(data.getRawData(), &phys, std::min(sizeof(ValueType), Size));
							}

							LOG(INFO) << "SomeIpBigEndianPolicy::toRaw completed";
						}

						template <typename ValueType, size_t Size>
						static void toPhysical(HwComDataObject<ValueType, Size>& data) noexcept
						{
							LOG(INFO) << "SomeIpBigEndianPolicy::toPhysical called";
							ValueType phys{};

							if constexpr (sizeof(ValueType) == 1)
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toPhysical 1-byte path";
								std::memcpy(&phys, data.getRawData(), 1);
							}
							else if constexpr (sizeof(ValueType) == 2)
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toPhysical 2-byte path";
								uint16_t rawVal; std::memcpy(&rawVal, data.getRawData(), 2);
								uint16_t val = ntohs(rawVal);
								std::memcpy(&phys, &val, 2);
							}
							else if constexpr (sizeof(ValueType) == 4)
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toPhysical 4-byte path";
								uint32_t rawVal; std::memcpy(&rawVal, data.getRawData(), 4);
								uint32_t val = ntohl(rawVal);
								std::memcpy(&phys, &val, 4);
							}
							else if constexpr (sizeof(ValueType) == 8)
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toPhysical 8-byte path";
								uint64_t rawVal; std::memcpy(&rawVal, data.getRawData(), 8);
								uint64_t val = myNtohll(rawVal);
								std::memcpy(&phys, &val, 8);
							}
							else
							{
								LOG(INFO) << "SomeIpBigEndianPolicy::toPhysical fallback path";
								std::memcpy(&phys, data.getRawData(), std::min(sizeof(ValueType), Size));
							}

							data.setPhysical(phys);
							LOG(INFO) << "SomeIpBigEndianPolicy::toPhysical completed";
						}

						template <size_t Size>
						static void toRaw(HwComDataObject<void, Size>&) noexcept
						{
							LOG(INFO) << "SomeIpBigEndianPolicy::toRaw<void> called (no-op)";
						}

						template <size_t Size>
						static void toPhysical(HwComDataObject<void, Size>&) noexcept
						{
							LOG(INFO) << "SomeIpBigEndianPolicy::toPhysical<void> called (no-op)";
						}
					};
				} // namespace HwSerializer

				//======================================================================================
				// Generic hardware communication data model
				//======================================================================================

				class HwComDataInterface
				{
				public:
					virtual ~HwComDataInterface() = default;

					virtual void setAddress(uint32_t setNewAddress) noexcept = 0;
					virtual uint32_t getAddress() const noexcept = 0;
					virtual uint16_t getLength() const noexcept = 0;
					virtual size_t getRawSize() const noexcept = 0;
					virtual const uint8_t* getRawData() const noexcept = 0;
					virtual uint8_t* getRawData() noexcept = 0;

					virtual uint8_t& operator[](size_t index) = 0;
					virtual const uint8_t& operator[](size_t index) const = 0;

					virtual void setRaw(const uint8_t* src, size_t length) noexcept = 0;
					virtual void setRaw(std::initializer_list<uint8_t> src) noexcept = 0;
				};

				//--------------------------------------------------------------------------------------
				// Base template class containing common data members/functions
				//--------------------------------------------------------------------------------------

				template <size_t Size>
				class HwComDataBase : public HwComDataInterface
				{
				public:
					explicit HwComDataBase(uint32_t addr) noexcept : address(addr), rawValue{} {}

					HwComDataBase(const HwComDataBase&) = delete;
					HwComDataBase& operator=(const HwComDataBase&) = delete;
					HwComDataBase(HwComDataBase&&) noexcept = default;
					HwComDataBase& operator=(HwComDataBase&&) noexcept = default;

					virtual void setAddress(uint32_t setNewAddress) noexcept = 0;
					uint32_t getAddress() const noexcept override { return address; }
					uint16_t getLength() const noexcept override { return static_cast<uint16_t>(Size); }
					size_t getRawSize() const noexcept override { return Size; }
					const uint8_t* getRawData() const noexcept override { return rawValue.data(); }
					uint8_t* getRawData() noexcept override { return rawValue.data(); }

					uint8_t& operator[](size_t index) override { return rawValue.at(index); }
					const uint8_t& operator[](size_t index) const override { return rawValue.at(index); }

					void setRaw(const uint8_t* src, size_t length) noexcept override
					{
						if (src == nullptr || length == 0)
						{
							std::memset(rawValue.data(), 0, Size);
							return;
						}
						const size_t copySize = std::min(length, Size);
						std::memcpy(rawValue.data(), src, copySize);
						if (copySize < Size)
						{
							std::memset(rawValue.data() + copySize, 0, Size - copySize);
						}
					}

					void setRaw(std::initializer_list<uint8_t> src) noexcept override
					{
						setRaw(src.begin(), src.size());
					}

				protected:
					uint32_t address;
					alignas(alignof(std::max_align_t)) std::array<uint8_t, Size> rawValue;
				};

				//--------------------------------------------------------------------------------------
				// Template for structured physical variables
				//--------------------------------------------------------------------------------------

				template <typename ValueType, size_t Size>
				class HwComDataObject : public HwComDataBase<Size>
				{
					static_assert(std::is_trivially_copyable_v<ValueType>, "ValueType must be a Trivially Copyable type!");
					static_assert(sizeof(ValueType) <= Size, "ValueSize is larger than the raw physical capacity!");

				public:
					explicit HwComDataObject(uint32_t addr) noexcept : HwComDataBase<Size>(addr), physicalValue{} {}

					ValueType getPhysical() const noexcept
					{
						return physicalValue;
					}

					void setPhysical(ValueType val) noexcept
					{
						physicalValue = val;
					}

					void setPhysicalRaw(ValueType val) noexcept
					{
						physicalValue = val;
						std::memset(this->getRawData(), 0, Size);
						std::memcpy(this->getRawData(), &physicalValue, sizeof(ValueType));
					}

					void setAddress(uint32_t addr) noexcept override
					{
						this->address = addr;
					}

					//======================================================================================
					// Generic template methods for serialization policies
					//======================================================================================

					template <typename SerializationPolicy>
					void toRaw(SerializationPolicy& policy) noexcept
					{
						policy.toRaw(*this);
					}

					template <typename SerializationPolicy>
					void toPhysical(SerializationPolicy& policy) noexcept
					{
						policy.toPhysical(*this);
					}

					//======================================================================================
					// Convenience methods for common serialization policies
					//======================================================================================

					void toRawBigEndian() noexcept
					{
						HwSerializer::SomeIpBigEndianPolicy::toRaw(*this);
					}

					void toRawDirectCopy() noexcept
					{
						HwSerializer::DirectCopyPolicy::toRaw(*this);
					}

					void toPhysicalBigEndian() noexcept
					{
						HwSerializer::SomeIpBigEndianPolicy::toPhysical(*this);
					}

					void toPhysicalDirectCopy() noexcept
					{
						HwSerializer::DirectCopyPolicy::toPhysical(*this);
					}

				private:
					ValueType physicalValue;
				};

				//--------------------------------------------------------------------------------------
				// Specialization for raw/typeless PDUs
				//--------------------------------------------------------------------------------------

				template <size_t Size>
				class HwComDataObject<void, Size> : public HwComDataBase<Size>
				{
				public:
					explicit HwComDataObject(uint32_t addr) noexcept : HwComDataBase<Size>(addr) {}
					void setAddress(uint32_t addr) noexcept override { this->address = addr; }
				};

				//======================================================================================
				// Free functions for HW buffer management
				//======================================================================================

				uint16_t setValueHWBuffer(bool resetCounter, const HwComDataInterface& element) noexcept;
				uint16_t readValueHWBuffer(bool resetCounter, const HwComDataInterface& element) noexcept;
				void clearHWBuffer() noexcept;

				//======================================================================================
				// PC_HW_Int_Light class
				//======================================================================================

				namespace PC_HW_Int_Light
				{
					class DLL_EXPORT_COMPONENT PC_HW_Int_Light
					{
					public:
						PC_HW_Int_Light();
						~PC_HW_Int_Light();

						std::string name = { "PC_HW_Interface" };
						const std::string STAR_PREFIX{ "FC3 Light: " };
						HANDLE handle_light;

						HwComDataObject<void, 0> read_Index{ 0 };

						const char* comRetValString(uint32_t retVal);
						bool openFlexCard_HW_Light(uint32_t cardNumber);
						bool closeFlexCard_HW_Light(uint32_t cardNumber);
						bool send_buffer(uint32_t cardNumber, t_hw_com_light_value* values, uint16_t count, u08 wait);
						bool read_buffer(uint32_t cardNumber, t_hw_com_light_value* values, uint16_t count);
						std::array<uint8_t, sizeof(double)> physValueToByteStream(double physValue);
						uint64_t physValueToUint64(double physValue);
						static uint64_t Htonll(uint64_t doubleBitRepresentation);
						static uint64_t Ntohll(uint64_t doubleBitRepresentation) noexcept;
						double byteArrayToDouble(uint8_t* dataArray);
						double uint64ToDouble(uint64_t dataBytes);
						double byteArrayToFloat(uint8_t* dataArray);
						const char* errorToString(t_hw_com_light_error error);

					protected:
						uint32_t cardUsed;
					};
				} // namespace PC_HW_Int_Light

			} // namespace Light
		} // namespace PC_HW_Interface
	} // namespace FlexCard3
} // namespace Plugins