/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.Receive_P220
/* SW-COMPONENT: C++-genericToolChainModelComponent
/* DESCRIPTION: Source is used to build a Labcar model component for a generic ToolChain, based on C++ code
/* COPYRIGHT: (C) 2025 Robert Bosch GmbH
/*
/* The reproduction, distribution and utilization of this file as
/* well as the communication of its contents to others without express
/* authorization is prohibited. Offenders will be held liable for the
/* payment of damages. All rights reserved in the event of the grant
/* of a patent, utility model or design.
/******************************************************************/

#include "../Receive.h"
#include "ModelCore/Quantity/Literals.h"
#include <iomanip>

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::Receive::P220(::model_core::common::time::SimulationTime* time_info)
{
	using namespace model_core::quantity::literals;

	if (CommonVars->TC10_Pulse_Status->quantity.get_value())
	{
		//ETH1 Initial Heartbeat PDU
		if (Receive_ETH1_HB_PDU_Init->quantity.get_value() && !CommonVars->EBCM_ETH1_Init_HB_Received->quantity.get_value())
		{
			if (Receive_ETH1_HB_PDU_TimeSinceLastSend->quantity.get_value() < cycleTimerETH1_ReceivePDUCount)
			{
				Receive_ETH1_HB_PDU_TimeSinceLastSend->quantity += none_t(cycleTimer);

				if (Receive_ETH1_HB_PDU_TimeSinceLastSend->quantity.get_value() >= cycleTimerETH1_ReceivePDUCount)
				{
					readValueHWBuffer(false, Receive_ETH1_PDU_Heartbeat);
					/*// Get raw PDU addresses
					const uint32_t getRawETH1PduAddress = static_cast<uint32_t>(CommonVars->EBCM_ETH1_HB_PDU_Get_Address->quantity.get_value());
					const uint16_t getRawETH1PduLength = static_cast<uint16_t>(CommonVars->EBCM_ETH1_HB_PDU_Length->quantity.get_value());

					// ✅ Use class member buffer and reset it
					m_receiveBuffer_ETH1_HB.assign(getRawETH1PduLength, 0x00);

					value_to_get[0].address = getRawETH1PduAddress;
					value_to_get[0].length = getRawETH1PduLength;
					value_to_get[0].data.buf = m_receiveBuffer_ETH1_HB.data();

					if (pc_hw_interface_light == nullptr)
					{
						Receive_ETH1_HB_PDU_TimeSinceLastSend->quantity = none_t(0);
						return;
					}
					auto start = std::chrono::high_resolution_clock::now();
					//bool success = pc_hw_interface_light->GetPhys_Multi_HW_light(cardNumber, value_to_get, 1);
					t_hw_com_light_error rcvError = hw_com_light_values_get(pc_hw_interface_light->handle_light, value_to_get, 1);
					auto stop = std::chrono::high_resolution_clock::now();
					auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

					if (rcvError == HW_COM_LIGHT_ERROR_OK)
					{
						if (m_receiveBuffer_ETH1_HB[8] == 0x0A && m_receiveBuffer_ETH1_HB[9] == 0x16 && m_receiveBuffer_ETH1_HB[10] == 0x06 && m_receiveBuffer_ETH1_HB[11] == 0x21)
						{
							CommonVars->EBCM_ETH1_Init_HB_Received->quantity = true;
						}
						else
						{
							CommonVars->EBCM_ETH1_Init_HB_Received->quantity = false;
						}
						//Get PDU Value HB ETH2
						ResetReceiveBuffer_0[0].address = CommonVars->EBCM_ETH1_HB_PDU_Set_Address->quantity.get_value(); //pduHBUpGetAddress_V23;
						ResetReceiveBuffer_0[0].length = CommonVars->EBCM_ETH1_HB_PDU_Length->quantity.get_value(); //lengthRawPduHB_V23;
						ResetReceiveBuffer_0[0].data.buf = GetRawPduHBBuffer_ETH1.data();
						//success = pc_hw_interface_light->PDU_Set_HW_Light(this->cardNumber, ResetReceiveBuffer_0, 1, wait);
						if (success) LOG(INFO) << "✓ EBCM ETH1 Receive Init PDU Reset sent successfully for ResetReceiveBuffer_0 ";
					}
					else
					{
						LOG(INFO) << "Failed" << "Error in Receive: " << pc_hw_interface_light->errorToString(rcvError);
					}*/
					Receive_ETH1_HB_PDU_TimeSinceLastSend->quantity = none_t(0);
					Test_ETH1->quantity++;
				}
			}
		}
		else
		{
			Receive_ETH1_HB_PDU_TimeSinceLastSend->quantity = none_t(0);
			Test_ETH1->quantity = none_t(0);
		}

		//ETH2 Initial Heartbeat PDU
		if (Receive_ETH2_HB_PDU_Init->quantity.get_value() && !CommonVars->EBCM_ETH2_Init_HB_Received->quantity.get_value())
		{
			if (Receive_ETH2_HB_PDU_TimeSinceLastSend->quantity.get_value() < cycleTimerETH2_ReceivePDUCount)
			{
				Receive_ETH2_HB_PDU_TimeSinceLastSend->quantity += none_t(cycleTimer);
				//LOG(INFO) << "Receive_ETH2_HB_PDU_TimeSinceLastSend: " << Receive_ETH2_HB_PDU_TimeSinceLastSend->quantity.get_value();
				if (Receive_ETH2_HB_PDU_TimeSinceLastSend->quantity.get_value() >= cycleTimerETH2_ReceivePDUCount)
				{
					readValueHWBuffer(false, Receive_ETH2_PDU_Heartbeat);
					/*// Get raw PDU addresses
					const uint32_t getRawETH2PduAddress = static_cast<uint32_t>(CommonVars->EBCM_ETH2_HB_PDU_Get_Address->quantity.get_value());
					const uint16_t getRawETH2PduLength = static_cast<uint16_t>(CommonVars->EBCM_ETH2_HB_PDU_Length->quantity.get_value());

					// ✅ Use class member buffer and reset it
					m_receiveBuffer_ETH2_HB.assign(getRawETH2PduLength, 0x00);

					value_to_get[0].address = getRawETH2PduAddress;
					value_to_get[0].length = getRawETH2PduLength;
					value_to_get[0].data.buf = m_receiveBuffer_ETH2_HB.data();

					if (pc_hw_interface_light == nullptr)
					{
						LOG(WARNING) << STAR_PREFIX << "Receive P220 -> pc_hw_interface_light is nullptr.";
						Receive_ETH2_HB_PDU_TimeSinceLastSend->quantity = none_t(0);
						return;
					}
					auto start = std::chrono::high_resolution_clock::now();
					//bool success = pc_hw_interface_light->GetPhys_Multi_HW_light(cardNumber, value_to_get, 1);
					t_hw_com_light_error rcvError = hw_com_light_values_get(pc_hw_interface_light->handle_light, value_to_get, 1);
					auto stop = std::chrono::high_resolution_clock::now();
					auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

					if (rcvError == HW_COM_LIGHT_ERROR_OK)
					{
						//if (m_receiveBuffer_ETH2_HB[8] == 0x1C && m_receiveBuffer_ETH2_HB[9] == 0x1D && m_receiveBuffer_ETH2_HB[10] == 0x1E && m_receiveBuffer_ETH2_HB[11] == 0x1F)
						if (m_receiveBuffer_ETH2_HB[8] == 0x0A && m_receiveBuffer_ETH2_HB[9] == 0x17 && m_receiveBuffer_ETH2_HB[10] == 0x06 && m_receiveBuffer_ETH2_HB[11] == 0x21)
						{
							CommonVars->EBCM_ETH2_Init_HB_Received->quantity = true;
						}
						else
						{
							CommonVars->EBCM_ETH2_Init_HB_Received->quantity = false;
						}
						//Get PDU Value HB ETH2
						ResetReceiveBuffer_2[0].address = CommonVars->EBCM_ETH2_HB_PDU_Set_Address->quantity.get_value(); //pduHBUpGetAddress_V23;
						ResetReceiveBuffer_2[0].length = CommonVars->EBCM_ETH2_HB_PDU_Length->quantity.get_value(); //lengthRawPduHB_V23;
						ResetReceiveBuffer_2[0].data.buf = GetRawPduHBBuffer_ETH2.data();
						//success = pc_hw_interface_light->PDU_Set_HW_Light(this->cardNumber, ResetReceiveBuffer_2, 1, wait);
						if (success) LOG(INFO) << "✓ EBCM ETH2 Receive Init PDU Reset sent successfully for ResetReceiveBuffer_2 ";
					}
					else
					{
						LOG(INFO) << "Failed" << "Error in Receive: " << pc_hw_interface_light->errorToString(rcvError);
					}
					*/
					Receive_ETH2_HB_PDU_TimeSinceLastSend->quantity = none_t(0);
					Test_ETH2->quantity++;
				}
			}
		}
		else
		{
			Receive_ETH2_HB_PDU_TimeSinceLastSend->quantity = none_t(0);
			Test_ETH2->quantity = none_t(0);
		}

		//ETH1 Info PDU
		if (Receive_ETH1_Info_PDU_Enable->quantity.get_value() && !CommonVars->EBCM_ETH1_Info_Response_Received->quantity.get_value() && !CommonVars->EBCM_ETH2_Info_Response_Received->quantity.get_value())
		{
			if (Receive_ETH1_InfoPDU_TimeSinceLastSend->quantity.get_value() < cycleTimer_Receive_ETH1_InfoPDUCount)
			{
				Receive_ETH1_InfoPDU_TimeSinceLastSend->quantity += none_t(cycleTimer);
				if (Receive_ETH1_InfoPDU_TimeSinceLastSend->quantity.get_value() >= cycleTimer_Receive_ETH1_InfoPDUCount)
				{
					readValueHWBuffer(false, Receive_ETH1_PDU_Info);
					/*const uint32_t getRawPduAddress = static_cast<uint32_t>(CommonVars->EBCM_ETH1_Info_PDU_Get_Address->quantity.get_value());
					const uint16_t getRawPduLength = static_cast<uint16_t>(CommonVars->EBCM_ETH1_Info_PDU_Length->quantity.get_value());

					// ✅ Use class member buffer and reset it
					m_receiveBuffer_ETH1_Info.assign(getRawPduLength, 0x00);

					value_to_get[0].address = getRawPduAddress;
					value_to_get[0].length = getRawPduLength;
					value_to_get[0].data.buf = m_receiveBuffer_ETH1_Info.data();

					if (pc_hw_interface_light == nullptr)
					{
						LOG(WARNING) << STAR_PREFIX << "Receive P220 -> pc_hw_interface_light is nullptr.";
						Receive_ETH1_InfoPDU_TimeSinceLastSend->quantity = none_t(0);
						return;
					}
					auto start = std::chrono::high_resolution_clock::now();
					//bool success = pc_hw_interface_light->GetPhys_Multi_HW_light(cardNumber, value_to_get, 1);
					t_hw_com_light_error rcvError = hw_com_light_values_get(pc_hw_interface_light->handle_light, value_to_get, 1);
					auto stop = std::chrono::high_resolution_clock::now();
					auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

					if (rcvError == HW_COM_LIGHT_ERROR_OK)
					{
						if (m_receiveBuffer_ETH1_Info[27] == 1)
						{
							CommonVars->EBCM_ETH1_Info_Response_Received->quantity = true;
						}
						else
						{
							CommonVars->EBCM_ETH1_Info_Response_Received->quantity = false;
						}
					}
					else
					{
						LOG(INFO) << "Failed" << "Error in Receive: " << pc_hw_interface_light->errorToString(rcvError);
					}*/
					Receive_ETH1_InfoPDU_TimeSinceLastSend->quantity = none_t(0);
				}
			}
		}
		else
		{
			Receive_ETH1_InfoPDU_TimeSinceLastSend->quantity = none_t(0);
		}

		//ETH2 Info PDU
		if (Receive_ETH2_Info_PDU_Enable->quantity.get_value() && !CommonVars->EBCM_ETH1_Info_Response_Received->quantity.get_value() && !CommonVars->EBCM_ETH2_Info_Response_Received->quantity.get_value())
		{
			if (Receive_ETH2_InfoPDU_TimeSinceLastSend->quantity.get_value() < cycleTimer_Receive_ETH2_InfoPDUCount)
			{
				Receive_ETH2_InfoPDU_TimeSinceLastSend->quantity += none_t(cycleTimer);
				if (Receive_ETH2_InfoPDU_TimeSinceLastSend->quantity.get_value() >= cycleTimer_Receive_ETH2_InfoPDUCount)
				{
					readValueHWBuffer(false, Receive_ETH2_PDU_Info);
					/*const uint32_t getRawPduAddress = static_cast<uint32_t>(CommonVars->EBCM_ETH2_Info_PDU_Get_Address->quantity.get_value());
					const uint16_t getRawPduLength = static_cast<uint16_t>(CommonVars->EBCM_ETH2_Info_PDU_Length->quantity.get_value());

					// ✅ Use class member buffer and reset it
					m_receiveBuffer_ETH2_Info.assign(getRawPduLength, 0x00);

					value_to_get[0].address = getRawPduAddress;
					value_to_get[0].length = getRawPduLength;
					value_to_get[0].data.buf = m_receiveBuffer_ETH2_Info.data();

					if (pc_hw_interface_light == nullptr)
					{
						LOG(WARNING) << STAR_PREFIX << "Receive P220 -> pc_hw_interface_light is nullptr.";
						Receive_ETH2_InfoPDU_TimeSinceLastSend->quantity = none_t(0);
						return;
					}
					auto start = std::chrono::high_resolution_clock::now();
					//bool success = pc_hw_interface_light->GetPhys_Multi_HW_light(cardNumber, value_to_get, 1);
					t_hw_com_light_error rcvError = hw_com_light_values_get(pc_hw_interface_light->handle_light, value_to_get, 1);
					auto stop = std::chrono::high_resolution_clock::now();
					auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

					if (rcvError == HW_COM_LIGHT_ERROR_OK)
					{
						if (m_receiveBuffer_ETH2_Info[27] == 1)
						{
							CommonVars->EBCM_ETH2_Info_Response_Received->quantity = true;
						}
						else
						{
							CommonVars->EBCM_ETH2_Info_Response_Received->quantity = false;
						}
					}
					else
					{
						LOG(INFO) << "Failed" << "Error in Receive: " << pc_hw_interface_light->errorToString(rcvError);
					}*/
					Receive_ETH2_InfoPDU_TimeSinceLastSend->quantity = none_t(0);
				}
			}
		}
		else
		{
			Receive_ETH2_InfoPDU_TimeSinceLastSend->quantity = none_t(0);
		}

		//SomeIP Signals
		if (Receive_Signal_Enable->quantity.get_value())
		{
			if (Receive_TimeSinceLastSend->quantity.get_value() < cycleTimer_ReceiveSignalCount)
			{
				Receive_TimeSinceLastSend->quantity += none_t(cycleTimer);
				if (Receive_TimeSinceLastSend->quantity.get_value() >= cycleTimer_ReceiveSignalCount)
				{
					readValueHWBuffer(false, receive_eth_VeBACR_l_eBstMCP__Sig_Signal);
					LOG(INFO) << "Receive P220 -> receive_eth_VeBACR_l_eBstMCP__Sig_Signal Addr: " << receive_eth_VeBACR_l_eBstMCP__Sig_Signal.getAddress()
						<< "Length :" << receive_eth_VeBACR_l_eBstMCP__Sig_Signal.getLength();

					readValueHWBuffer(false, receive_eth_VeBACR_l_eBstMCS__Sig_Signal);
					LOG(INFO) << "Receive P220 -> receive_eth_VeBACR_l_eBstMCS__Sig_Signal Addr: " << receive_eth_VeBACR_l_eBstMCS__Sig_Signal.getAddress()
						<< "Length :" << receive_eth_VeBACR_l_eBstMCS__Sig_Signal.getLength();
					/*//VeBACR_Cnt_eBstWS_PulsLfP = > Phys: 5911504, length 8; Raw: 5933392, length 2
					const uint32_t getRawPduAddress1 = static_cast<uint32_t>(5911504);
					const uint16_t getRawPduLength1 = static_cast<uint16_t>(8);
					const uint32_t getRawPduAddress1Value = static_cast<uint32_t>(5933392);
					const uint16_t getRawPduLength1Value = static_cast<uint16_t>(2);

					//VeBACR_l_eBstMCP = > Phys: 5910188, length 8; Raw: 5922768, length 4
					const uint32_t getRawPduAddress2 = static_cast<uint32_t>(5910188);
					const uint16_t getRawPduLength2 = static_cast<uint16_t>(8);
					const uint32_t getRawPduAddress2Value = static_cast<uint32_t>(5922768);
					const uint16_t getRawPduLength2Value = static_cast<uint16_t>(4);

					//VeBACR_d_eBstWS_VdaBitsLfP = > Phys: 5910248, length 8; Raw: 5933128, length 2
					const uint32_t getRawPduAddress3 = static_cast<uint32_t>(5910248);
					const uint16_t getRawPduLength3 = static_cast<uint16_t>(8);
					const uint32_t getRawPduAddress3Value = static_cast<uint32_t>(5933128);
					const uint16_t getRawPduLength3Value = static_cast<uint16_t>(2);

					// buffers
					m_receiveBuffer_Signals.assign(getRawPduLength1, 0xff);
					m_receiveBuffer_Signals2.assign(getRawPduLength2, 0xff);
					m_receiveBuffer_Signals3.assign(getRawPduLength3, 0xff);

					uint32_t val_1 = 0xFFFFFFFF;
					uint32_t val_2 = 0xFFFFFFFF;
					uint32_t val_3 = 0xFFFFFFFF;

					const uint16_t hwGetBufferSize = 6;

					value_to_get[0].address = getRawPduAddress1;
					value_to_get[0].length = getRawPduLength1;
					value_to_get[0].data.buf = m_receiveBuffer_Signals.data();

					value_to_get[1].address = getRawPduAddress2;
					value_to_get[1].length = getRawPduLength2;
					value_to_get[1].data.buf = m_receiveBuffer_Signals2.data();

					value_to_get[2].address = getRawPduAddress3;
					value_to_get[2].length = getRawPduLength3;
					value_to_get[2].data.buf = m_receiveBuffer_Signals3.data();

					value_to_get[3].address = getRawPduAddress1Value;
					value_to_get[3].length = getRawPduLength1Value;
					value_to_get[3].data.value = val_1;

					value_to_get[4].address = getRawPduAddress2Value;
					value_to_get[4].length = getRawPduLength2Value;
					value_to_get[4].data.value = val_2;

					value_to_get[5].address = getRawPduAddress3Value;
					value_to_get[5].length = getRawPduLength3Value;
					value_to_get[5].data.value = val_3;

					if (pc_hw_interface_light == nullptr)
					{
						LOG(WARNING) << STAR_PREFIX << "Receive P220 -> pc_hw_interface_light is nullptr.";
						Receive_TimeSinceLastSend->quantity = none_t(0);
						return;
					}

					auto start = std::chrono::high_resolution_clock::now();

					t_hw_com_light_error rcvError = hw_com_light_values_get(pc_hw_interface_light->handle_light, value_to_get, hwGetBufferSize);
					//const bool success = pc_hw_interface_light->SignalPhys_MultiGet_HW_Light(cardNumber, value_to_get, hwGetBufferSize);

					auto stop = std::chrono::high_resolution_clock::now();
					auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

					if (rcvError == HW_COM_LIGHT_ERROR_OK)
					{
						double network_value = pc_hw_interface_light->byteArrayToDouble(m_receiveBuffer_Signals.data());
						double network_value1 = pc_hw_interface_light->byteArrayToDouble(m_receiveBuffer_Signals2.data());
						double network_value2 = pc_hw_interface_light->byteArrayToDouble(m_receiveBuffer_Signals3.data());

						//Buffer 0
						std::ostringstream buf0;
						buf0 << "Address: " << value_to_get[0].address << " bytes: ";
						for (uint8_t byte : m_receiveBuffer_Signals)
							buf0 << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
						//LOG(INFO) << STAR_PREFIX << buf0.str() << " Result: " << network_value;

						//Buffer 1
						std::ostringstream buf1;
						buf1 << "Address: " << value_to_get[1].address << " bytes: ";
						for (uint8_t byte : m_receiveBuffer_Signals2)
							buf1 << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
						//LOG(INFO) << STAR_PREFIX << buf1.str() << " Result1: " << network_value1;

						//Buffer 2
						std::ostringstream buf2;
						buf2 << "Address: " << value_to_get[2].address << " bytes: ";
						for (uint8_t byte : m_receiveBuffer_Signals3)
							buf2 << "0x" << std::hex << std::setw(2) << std::setfill('0') << (int)byte << " ";
						//LOG(INFO) << STAR_PREFIX << buf2.str() << " Result2: " << network_value2;

						//value_to_get[2].data.value = val_1;
						//value_to_get[3].data.value = val_2;
						val_1 = value_to_get[3].data.value;
						val_2 = value_to_get[4].data.value;
						val_3 = value_to_get[5].data.value;

						//LOG(INFO) << STAR_PREFIX << "Raw Result2: " << val_1;
						//LOG(INFO) << STAR_PREFIX << "Raw Result3: " << val_2;
						//LOG(INFO) << STAR_PREFIX << "Raw Result4: " << val_3;

						VeBACR_Cnt_eBstWS_PulsLfP__Sig->quantity = (none_t)network_value;
						VeBACR_l_eBstMCP__Sig->quantity = (none_t) network_value1;
						VeBACR_d_eBstWS_VdaBitsLfP__Sig->quantity = (none_t) network_value2;

						//Assign to stroke
						CommonVars->MS_stroke->quantity = (millimeter_t)VeBACR_l_eBstMCP__Sig->quantity.get_value();
					}
					else
					{
						LOG(INFO) << "Failed"<< "Error in Receive: "<< pc_hw_interface_light->errorToString(rcvError);
						VeBACR_Cnt_eBstWS_PulsLfP__Sig->quantity = 0_none;
						VeBACR_l_eBstMCP__Sig->quantity = 0_none;
						VeBACR_d_eBstWS_VdaBitsLfP__Sig->quantity = 0_none;
					}*/
					Receive_TimeSinceLastSend->quantity = none_t(0);
				}
			}
		}
		else
		{
			Receive_TimeSinceLastSend->quantity = none_t(0);
		}
	}
	else
	{
		// Reset all receive timers when TC10 pulse is OFF
		Receive_ETH1_HB_PDU_TimeSinceLastSend->quantity = none_t(0);
		Receive_ETH2_HB_PDU_TimeSinceLastSend->quantity = none_t(0);
		Receive_ETH1_InfoPDU_TimeSinceLastSend->quantity = none_t(0);
		Receive_ETH2_InfoPDU_TimeSinceLastSend->quantity = none_t(0);
		Receive_TimeSinceLastSend->quantity = none_t(0);

		// Reset heartbeat receive state so next FALSE->TRUE cycle behaves like a fresh start
		CommonVars->EBCM_ETH1_Init_HB_Received->quantity = false;
		CommonVars->EBCM_ETH1_Cyclic_HB_Received->quantity = false;
		CommonVars->EBCM_ETH2_Init_HB_Received->quantity = false;
		CommonVars->EBCM_ETH2_Cyclic_HB_Received->quantity = false;

		// Reset info response state
		CommonVars->EBCM_ETH1_Info_Response_Received->quantity = false;
		CommonVars->EBCM_ETH2_Info_Response_Received->quantity = false;
	}
}