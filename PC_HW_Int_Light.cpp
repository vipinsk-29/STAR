#include "PC_HW_Int_Light.h"
#include <g3log/g3log.hpp>
#include <g3log/loglevels.hpp>

// PC_HW_Int_Light.cpp — add at the top after includes
// Single definition of the shared HW buffer
t_hw_com_light_value s_hwBuffer[HW_BUFFER_SIZE] = {};
t_hw_com_light_value r_hwBuffer[HW_BUFFER_SIZE] = {};
std::array<std::vector<uint8_t>, HW_BUFFER_SIZE> m_receiveBuffers;

Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::PC_HW_Int_Light()
{
	handle_light = nullptr;
	name = "PC_HW_Int_Light";
	cardUsed = 1;
}

Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::~PC_HW_Int_Light()
{

}

const char* Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::comRetValString(uint32_t retVal)
{
	t_hw_com_light_error error = static_cast<t_hw_com_light_error>(retVal);
	return errorToString(error);  // ✅ Call the actual conversion function
}

bool Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::openFlexCard_HW_Light(uint32_t cardNumber)
{
	LOG(INFO) << this->STAR_PREFIX << "========== FlexCard3 Light Communication Open START ==========";
	LOG(INFO) << this->STAR_PREFIX << "Requested card number: " << cardNumber;

	char device_path_buffer[] = "/dev/flexcard_ng-dt0/raw";

	// ✅ 1. Log timestamp before blocking call
	auto start_time = std::chrono::steady_clock::now();
	LOG(INFO) << this->STAR_PREFIX << "========== CALLING hw_com_light_create NOW ==========";
	LOG(INFO) << this->STAR_PREFIX << "Parameters: device=" << device_path_buffer
		<< ", port=" << PORT << ", timeout=" << TIMEOUT;

	t_hw_com_light_error result = HW_COM_LIGHT_ERROR_OK;

	// ✅ 2. The actual call with immediate post-call logging
	result = hw_com_light_create(&handle_light, device_path_buffer, PORT, TIMEOUT);

	// ✅ 3. Log timestamp after call returns
	auto end_time = std::chrono::steady_clock::now();
	auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	LOG(INFO) << this->STAR_PREFIX << "========== hw_com_light_create RETURNED ==========";
	LOG(INFO) << this->STAR_PREFIX << "Call duration: " << duration_ms << " ms";
	LOG(INFO) << this->STAR_PREFIX << "Result code: " << static_cast<uint32_t>(result);
	LOG(INFO) << this->STAR_PREFIX << "Result string: " << errorToString(result);
	LOG(INFO) << this->STAR_PREFIX << "handle_light after create: " << static_cast<void*>(handle_light);

	if (result == HW_COM_LIGHT_ERROR_OK) {
		LOG(INFO) << this->STAR_PREFIX << "✓ SUCCESS: Handle obtained successfully";

		// ✅ 4. Verify handle is valid
		if (handle_light == nullptr) {
			LOG(WARNING) << this->STAR_PREFIX << "FATAL: Result is OK but handle is still nullptr!";
			return false;
		}
	}
	else {
		LOG(WARNING) << this->STAR_PREFIX << "✗ FAILED to create handle";
		LOG(WARNING) << this->STAR_PREFIX << "Error details: " << errorToString(result);

		// ✅ 5. Log specific error context
		switch (result) {
		case HW_COM_LIGHT_ERROR_BAD_PARAMETER:
			LOG(WARNING) << this->STAR_PREFIX << "Possible causes: Invalid device path, port, or timeout";
			break;
		case HW_COM_LIGHT_ERROR_FAILED_TO_SEND_REQUEST:
			LOG(WARNING) << this->STAR_PREFIX << "Possible causes: Network connectivity issues, firewall blocking port " << PORT;
			break;
		case HW_COM_LIGHT_ERROR_FAILED_TO_RECEIVE_RESPONSE:
			LOG(WARNING) << this->STAR_PREFIX << "Possible causes: Device not responding, wrong port, timeout too short";
			break;
		case HW_COM_LIGHT_ERROR_FAILED_TO_INIT_WINSOCK:
			LOG(WARNING) << this->STAR_PREFIX << "Network initialization failed";
			break;
		default:
			LOG(WARNING) << this->STAR_PREFIX << "Unexpected error code";
			break;
		}
	}

	LOG(INFO) << this->STAR_PREFIX << "========== FlexCard3 Light Communication Open END ==========";
	return result == HW_COM_LIGHT_ERROR_OK;
}

bool Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::closeFlexCard_HW_Light(uint32_t cardNumber)
{
	t_hw_com_light_error result = hw_com_light_destroy(handle_light);
	LOG(INFO) << this->STAR_PREFIX << "FlexCard Light close result: " << static_cast<uint32_t>(result) << " " << comRetValString(result);
	return result == HW_COM_LIGHT_ERROR_OK;
}

bool Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::send_buffer(uint32_t cardNumber, t_hw_com_light_value* values, uint16_t count, u08 wait)
{
	if (handle_light == nullptr) {
		LOG(WARNING) << STAR_PREFIX << "send_buffer: handle_light is nullptr";
		return false;
	}
	if (values == nullptr || count == 0) {
		LOG(WARNING) << STAR_PREFIX << "send_buffer: invalid args values=" << values
			<< ", count=" << count;
		return false;
	}

	t_hw_com_light_error retVal = hw_com_light_values_set(handle_light, values, count, wait);

	if (retVal == HW_COM_LIGHT_ERROR_OK) {
		LOG(INFO) << this->STAR_PREFIX << "send_buffer succeeded";

		// ✅ 4. Verify handle is valid
		if (handle_light == nullptr) {
			LOG(WARNING) << this->STAR_PREFIX << "FATAL: Result is OK but handle is still nullptr!";
			return false;
		}
	}
	else
	{
		LOG(WARNING) << this->STAR_PREFIX << "Error details: " << errorToString(retVal);

		// ✅ 5. Log specific error context
		switch (retVal)
		{
		case HW_COM_LIGHT_ERROR_OK:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_OK";
			break;

		case HW_COM_LIGHT_ERROR_BAD_PARAMETER:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_BAD_PARAMETER - Invalid parameter provided";
			break;

		case HW_COM_LIGHT_ERROR_BAD_HANDLE:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_BAD_HANDLE - Invalid hardware handle";
			break;

		case HW_COM_LIGHT_ERROR_FAILED_TO_SEND_REQUEST:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_FAILED_TO_SEND_REQUEST - Failed to send request to hardware";
			break;

		case HW_COM_LIGHT_ERROR_FAILED_TO_RECEIVE_RESPONSE:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_FAILED_TO_RECEIVE_RESPONSE - Failed to receive response from hardware";
			break;

		case HW_COM_LIGHT_ERROR_WRONG_RESPONSE_SOURCE:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_WRONG_RESPONSE_SOURCE - Response came from unexpected source";
			break;

		case HW_COM_LIGHT_ERROR_OUT_OF_MEMORY:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_OUT_OF_MEMORY - Insufficient memory allocated";
			break;

		case HW_COM_LIGHT_ERROR_FAILED_TO_INIT_WINSOCK:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_FAILED_TO_INIT_WINSOCK - Failed to initialize Windows Socket";
			break;

		case HW_COM_LIGHT_ERROR_BAD_RESPONSE_FORMAT:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_BAD_RESPONSE_FORMAT - Response format is invalid";
			break;

		case HW_COM_LIGHT_ERROR_RESPONSE_UNKNOWN:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_RESPONSE_UNKNOWN - Unknown response received";
			break;

		case HW_COM_LIGHT_ERROR_RESPONSE_INCOMPLETE:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_RESPONSE_INCOMPLETE - Response is incomplete or truncated";
			break;

		case HW_COM_LIGHT_ERROR_BAD_RESPONSE_COUNTER:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_BAD_RESPONSE_COUNTER - Response counter mismatch";
			break;

		case HW_COM_LIGHT_ERROR_RESPONSE_NACK:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_RESPONSE_NACK - Hardware sent NACK (negative acknowledgment)";
			break;

		case HW_COM_LIGHT_ERROR_FAILED:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_FAILED - Generic hardware communication failure";
			break;

		default:
			LOG(INFO) << "UNKNOWN_ERROR - Unexpected error code: " << static_cast<int>(retVal);
			break;
		}
	}
	return (retVal == HW_COM_LIGHT_ERROR_OK);
}


bool Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::read_buffer(uint32_t cardNumber, t_hw_com_light_value* values, uint16_t count)
{
	if (handle_light == nullptr) {
		LOG(WARNING) << STAR_PREFIX << "read_buffer: handle_light is nullptr";
		return false;
	}

	if (values == nullptr || count == 0) {
		LOG(WARNING) << STAR_PREFIX << "read_buffer: invalid args values=" << values
			<< ", count=" << count;
		return false;
	}

	t_hw_com_light_error retVal = hw_com_light_values_get(handle_light, values, count);

	if (retVal == HW_COM_LIGHT_ERROR_OK) {
		LOG(INFO) << this->STAR_PREFIX << "read_buffer succeeded";

		// ✅ 4. Verify handle is valid
		if (handle_light == nullptr) {
			LOG(WARNING) << this->STAR_PREFIX << "FATAL: Result is OK but handle is still nullptr!";
			return false;
		}

		//need to add logic for reading the data to proceed further
	}
	else
	{
		LOG(WARNING) << this->STAR_PREFIX << "Error details: " << errorToString(retVal);

		// ✅ 5. Log specific error context
		switch (retVal)
		{
		case HW_COM_LIGHT_ERROR_OK:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_OK";
			break;

		case HW_COM_LIGHT_ERROR_BAD_PARAMETER:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_BAD_PARAMETER - Invalid parameter provided";
			break;

		case HW_COM_LIGHT_ERROR_BAD_HANDLE:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_BAD_HANDLE - Invalid hardware handle";
			break;

		case HW_COM_LIGHT_ERROR_FAILED_TO_SEND_REQUEST:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_FAILED_TO_SEND_REQUEST - Failed to send request to hardware";
			break;

		case HW_COM_LIGHT_ERROR_FAILED_TO_RECEIVE_RESPONSE:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_FAILED_TO_RECEIVE_RESPONSE - Failed to receive response from hardware";
			break;

		case HW_COM_LIGHT_ERROR_WRONG_RESPONSE_SOURCE:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_WRONG_RESPONSE_SOURCE - Response came from unexpected source";
			break;

		case HW_COM_LIGHT_ERROR_OUT_OF_MEMORY:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_OUT_OF_MEMORY - Insufficient memory allocated";
			break;

		case HW_COM_LIGHT_ERROR_FAILED_TO_INIT_WINSOCK:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_FAILED_TO_INIT_WINSOCK - Failed to initialize Windows Socket";
			break;

		case HW_COM_LIGHT_ERROR_BAD_RESPONSE_FORMAT:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_BAD_RESPONSE_FORMAT - Response format is invalid";
			break;

		case HW_COM_LIGHT_ERROR_RESPONSE_UNKNOWN:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_RESPONSE_UNKNOWN - Unknown response received";
			break;

		case HW_COM_LIGHT_ERROR_RESPONSE_INCOMPLETE:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_RESPONSE_INCOMPLETE - Response is incomplete or truncated";
			break;

		case HW_COM_LIGHT_ERROR_BAD_RESPONSE_COUNTER:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_BAD_RESPONSE_COUNTER - Response counter mismatch";
			break;

		case HW_COM_LIGHT_ERROR_RESPONSE_NACK:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_RESPONSE_NACK - Hardware sent NACK (negative acknowledgment)";
			break;

		case HW_COM_LIGHT_ERROR_FAILED:
			LOG(INFO) << "HW_COM_LIGHT_ERROR_FAILED - Generic hardware communication failure";
			break;

		default:
			LOG(INFO) << "UNKNOWN_ERROR - Unexpected error code: " << static_cast<int>(retVal);
			break;
		}
	}
	return (retVal == HW_COM_LIGHT_ERROR_OK);
}

// Convert double to big-endian byte array
std::array<uint8_t, sizeof(double)> Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::physValueToByteStream(double physValue)
{
	std::array<uint8_t, sizeof(double)> byteArray;
	uint64_t doubleBitRepresentation;

	// Get the raw bits of the double as a uint64_t
	std::memcpy(&doubleBitRepresentation, &physValue, sizeof(double));

	// Convert uint64_t bit representation to network byte order (Big-Endian)
	uint64_t networkBitRepresentation = Htonll(doubleBitRepresentation);

	// Copy the bytes from the networkBitRepresentation into the byteArray
	std::memcpy(byteArray.data(), &networkBitRepresentation, sizeof(uint64_t));
	return byteArray;
}

// @brief convert double (phys) value to Big Endian representation
inline uint64_t Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::physValueToUint64(double physValue)
{
	uint64_t doubleBitRepresentation;
	// Get the raw bits of the double as a uint64_t
	std::memcpy(&doubleBitRepresentation, &physValue, sizeof(double));
	// Convert uint64_t bit representation to network byte order (Big-Endian)
	uint64_t networkBitRepresentation = Htonll(doubleBitRepresentation);
	return networkBitRepresentation;
}

// Convert 64-bit integer to network byte order (big-endian)
uint64_t Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::Htonll(uint64_t doubleBitRepresentation)
{
	if (kIsLittleEndian)
	{
		uint32_t high_part_host_order = static_cast<uint32_t>(doubleBitRepresentation >> 32);
		uint32_t low_part_host_order = static_cast<uint32_t>(doubleBitRepresentation & 0xFFFFFFFFULL);
		return (static_cast<uint64_t>(htonl(low_part_host_order)) << 32) | htonl(high_part_host_order);
	}
	else
	{
		// Host is Big-Endian
		return doubleBitRepresentation;
	}
}

uint64_t Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::Ntohll(uint64_t doubleBitRepresentation) noexcept
{
	return Htonll(doubleBitRepresentation);  // ✅ Symmetric conversion for network to host
}

double Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::byteArrayToDouble(uint8_t* dataArray)
{
	double output = 0.0;
	uint64_t rawBytes = 0;
	uint32_t arraysize = sizeof(rawBytes) - 1;
	memcpy(&rawBytes, dataArray, sizeof(rawBytes));

	uint64_t hostOrderedBytes;
	if (kIsLittleEndian) {
		// If host is little-endian, and dataArray is big-endian, we need to swap.
		hostOrderedBytes = htobe64(rawBytes); // The htobe64 macro should handle the swap on little-endian
	}
	else {
		// If host is big-endian, no swap needed if dataArray is big-endian.
		hostOrderedBytes = rawBytes;
	}
	memcpy(&output, &hostOrderedBytes, sizeof(output));
	return output;
}

double Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::uint64ToDouble(uint64_t dataBytes)
{
	double output = 0.0;
	uint64_t swappedBytes = 0;

	//byteswap
	swappedBytes = htobe64(dataBytes);

	//double conversion
	memcpy(&output, &swappedBytes, sizeof(output));
	return output;
}

double Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::byteArrayToFloat(uint8_t* dataArray)
{
	float output = 0.0;
	uint32_t rawBytes;
	uint32_t arraysize = sizeof(rawBytes) - 1;
	std::cout << "Before Byteswap received from FC3 MSB printed first: " << arraysize << std::endl;
	for (int32_t i = arraysize; i >= 0; i--)
	{
		std::cout << "0x" << std::hex << static_cast<int>(dataArray[i]) << " ";
	}
	std::cout << std::dec << std::endl;
	memcpy(&rawBytes, dataArray, sizeof(rawBytes));
	uint32_t hostOrderedBytes = ntohl(rawBytes);
	memcpy(&output, &hostOrderedBytes, sizeof(output));
	return static_cast<double>(output);
}

const char* Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light::errorToString(t_hw_com_light_error error)
{
	switch (error)
	{
	case HW_COM_LIGHT_ERROR_OK: return "HW_COM_LIGHT_ERROR_OK";
	case HW_COM_LIGHT_ERROR_BAD_PARAMETER: return "HW_COM_LIGHT_ERROR_BAD_PARAMETER";
	case HW_COM_LIGHT_ERROR_BAD_HANDLE: return "HW_COM_LIGHT_ERROR_BAD_HANDLE";
	case HW_COM_LIGHT_ERROR_FAILED_TO_SEND_REQUEST: return "HW_COM_LIGHT_ERROR_FAILED_TO_SEND_REQUEST";
	case HW_COM_LIGHT_ERROR_FAILED_TO_RECEIVE_RESPONSE: return "HW_COM_LIGHT_ERROR_FAILED_TO_RECEIVE_RESPONSE";
	case HW_COM_LIGHT_ERROR_WRONG_RESPONSE_SOURCE: return "HW_COM_LIGHT_ERROR_WRONG_RESPONSE_SOURCE";
	case HW_COM_LIGHT_ERROR_OUT_OF_MEMORY: return "HW_COM_LIGHT_ERROR_OUT_OF_MEMORY";
	case HW_COM_LIGHT_ERROR_FAILED_TO_INIT_WINSOCK: return "HW_COM_LIGHT_ERROR_FAILED_TO_INIT_WINSOCK";
	case HW_COM_LIGHT_ERROR_BAD_RESPONSE_FORMAT: return "HW_COM_LIGHT_ERROR_BAD_RESPONSE_FORMAT";
	case HW_COM_LIGHT_ERROR_RESPONSE_UNKNOWN: return "HW_COM_LIGHT_ERROR_RESPONSE_UNKNOWN";
	case HW_COM_LIGHT_ERROR_RESPONSE_INCOMPLETE: return "HW_COM_LIGHT_ERROR_RESPONSE_INCOMPLETE";
	case HW_COM_LIGHT_ERROR_BAD_RESPONSE_COUNTER: return "HW_COM_LIGHT_ERROR_BAD_RESPONSE_COUNTER";
	case HW_COM_LIGHT_ERROR_RESPONSE_NACK: return "HW_COM_LIGHT_ERROR_RESPONSE_NACK";
	case HW_COM_LIGHT_ERROR_FAILED: return "HW_COM_LIGHT_ERROR_FAILED";
	default: return "UNKNOWN_ERROR";
	}
}

uint16_t Plugins::FlexCard3::PC_HW_Interface::Light::setValueHWBuffer(bool resetCounter, const HwComDataInterface& element) noexcept
{
	static uint16_t slotIndex = 0;

	if (slotIndex >= HW_BUFFER_SIZE) return 9999;
	if (resetCounter == true) {
		const uint16_t lastValueBeforeReset = slotIndex;
		slotIndex = 0;
		return lastValueBeforeReset;
	}

	// Overwrite the slot data cleanly for this cycle
	s_hwBuffer[slotIndex].address = element.getAddress();
	s_hwBuffer[slotIndex].length = element.getLength(); // Direct, unified length mapping

	if (s_hwBuffer[slotIndex].length > 4) {
		// Zero-Copy Pointer Binding: Point directly to the stable buffer within the persistent class
		s_hwBuffer[slotIndex].data.buf = const_cast<uint8_t*>(element.getRawData());

	}
	else {
		// Direct Value Copy: Safely reset the ENTIRE 64-bit union space first.
			// This is critical on 64-bit systems to ensure no old upper-byte pointer residues
			// remain in the buffer from previous cycles when writing a 32-bit scalar.
		s_hwBuffer[slotIndex].data.buf = nullptr;

		if (s_hwBuffer[slotIndex].length > 0) {
			// We use memcpy here to safely copy up to 4 bytes. Directly casting to a uint32_t *
				// would trigger a buffer overread if getLength() < 4 (e.g. 1 or 2 bytes).
			std::memcpy(&s_hwBuffer[slotIndex].data.value, element.getRawData(),
				s_hwBuffer[slotIndex].length);
		}
	}
	return ++slotIndex;  // Increment for the next slot
}

uint16_t Plugins::FlexCard3::PC_HW_Interface::Light::readValueHWBuffer(bool resetCounter, const HwComDataInterface& element) noexcept
{
	static uint16_t slotIndex = 0;

	if (slotIndex >= HW_BUFFER_SIZE)
	{
		LOG(INFO) << "[readValueHWBuffer] slotIndex overflow: slotIndex=" << slotIndex << ", HW_BUFFER_SIZE=" << HW_BUFFER_SIZE << ". Returning 1111.";
		return 1111;
	}

	if (resetCounter == true)
	{
		const uint16_t lastValueBeforeReset = slotIndex;
		slotIndex = 0;
		//LOG(INFO) << "[readValueHWBuffer] reset requested. lastValueBeforeReset=" << lastValueBeforeReset << ", slotIndex reset to 0";
		return lastValueBeforeReset;
	}

	const auto length = element.getLength();
	const auto address = element.getAddress();
	const auto currentSlotIndex = static_cast<size_t>(slotIndex);

	if (length == 0)
	{
		LOG(WARNING) << "[readValueHWBuffer] element length is 0 for address=" << address;
	}

	// Overwrite the slot data cleanly for this cycle
	r_hwBuffer[slotIndex].address = address;
	r_hwBuffer[slotIndex].length = length; // Direct, unified length mapping
	
	if (length > 4)		//PDU will be considered as 0xFF if length > 4
	{
		if (currentSlotIndex >= m_receiveBuffers.size())
		{
			LOG(WARNING) << "[readValueHWBuffer] receive buffer index overflow: slotIndex=" << slotIndex;
			return 1111;
		}

		auto& receiveBuffer = m_receiveBuffers[currentSlotIndex];
		receiveBuffer.assign(length, 0xFF);
		r_hwBuffer[slotIndex].data.buf = receiveBuffer.data();
	}
	else				// For lengths <= 4, we can safely use the value field for RAW Signal data. We will initialize it to 0xFFFFFFFF to indicate an uninitialized state.
	{
		uint32_t val_1 = 0xFFFFFFFF;
		r_hwBuffer[slotIndex].data.value = val_1;
	}

	LOG(INFO) << "[readValueHWBuffer] prepared slotIndex=" << slotIndex << ", address=" << r_hwBuffer[slotIndex].address << ", length=" << r_hwBuffer[slotIndex].length << ", data.buf=" << static_cast<const void*>(r_hwBuffer[slotIndex].data.buf);

	return ++slotIndex; // Increment for the next slot
}

//======================================================================================
// Free functions — HW buffer management
//======================================================================================
// Helper utility to clear the workspace array, preparing it for the next cycle

void Plugins::FlexCard3::PC_HW_Interface::Light::clearHWBuffer() noexcept {
	std::memset(s_hwBuffer, 0, sizeof(s_hwBuffer));
	std::memset(r_hwBuffer, 0, sizeof(r_hwBuffer));
	for (auto& receiveBuffer : m_receiveBuffers)
	{
		receiveBuffer.clear();
	}
}