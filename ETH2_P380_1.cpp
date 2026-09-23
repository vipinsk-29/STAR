/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.ETH2_P380_1
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

#include "../ETH2.h"
#include "ModelCore/Quantity/Literals.h"
using namespace Plugins::FlexCard3::PC_HW_Interface::Light;

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH2::P380_1(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;
	wait = CommonVars->send_wait_ctrl->quantity.get_value();

	// Check if TC10_Pulse_Status is true
	if (CommonVars->TC10_Pulse_Status->quantity.get_value())
	{
		//ETH2_Node_Used is true (Normal Operation)
		if (ETH2_Node_Used->quantity.get_value())
		{
			if (!Init)
			{
				ETH2_PDU_WuP.setRaw(setRawPduWakeUpBuffer_V23.data(), CommonVars->CCU_ETH2_WuP_PDU_Length->quantity.get_value());
				setValueHWBuffer(false, ETH2_PDU_WuP);
				setValueHWBuffer(false, ETH2_Frame_WuP);

				ETH2_PDU_Heartbeat.setRaw(setRawPduHBBuffer_V23.data(), CommonVars->CCU_ETH2_HB_PDU_Length->quantity.get_value());
				setValueHWBuffer(false, ETH2_PDU_Heartbeat);
				setValueHWBuffer(false, ETH2_Frame_Heartbeat);

				ETH2_PDU_Info.setRaw(setRawPduInfoBuffer_V23.data(), 28); // CommonVars->CCU_ETH2_Info_PDU_Length->quantity.get_value());
				setValueHWBuffer(false, ETH2_PDU_Info);
				setValueHWBuffer(false, ETH2_Frame_Info);

				if (ETH2_WuP_Init_Send_Count->quantity == 0_none)
				{
					WuP_Cyclic_Control = false;
					ETH2_Custom_Timing_WuP.setPhysicalRaw(10);
					setValueHWBuffer(false, ETH2_Custom_Timing_WuP);
					LOG(INFO) << "ETH2 WuP Cycletime set to 10";
				}

				Init = true;
			}

			//ETH2_WuP_PDU
			if (ETH2_WuP_PDU_Used->quantity.get_value())
			{
				//WuP Init PDU will be sent for ETH2_WuP_Init_Send_Max times with 10mS interval, 
				if (ETH2_WuP_Init_Send_Count->quantity.get_value() < ETH2_WuP_Init_Send_Max->quantity.get_value())
				{
					if (ETH2_WuP_TimeSinceLastSend->quantity.get_value() < cycleTimeWuPInitTickCount)
					{
						ETH2_WuP_TimeSinceLastSend->quantity += none_t(cycleTimer);
						if (ETH2_WuP_TimeSinceLastSend->quantity.get_value() >= cycleTimeWuPInitTickCount)
						{
							ETH2_WuP_TimeSinceLastSend->quantity = none_t(0);
							ETH2_WuP_Init_Send_Count->quantity++;
						}
					}
				}
				else
				{
					if (ETH2_WuP_Init_Send_Count->quantity.get_value() >= ETH2_WuP_Init_Send_Max->quantity.get_value() && !WuP_Cyclic_Control)
					{
						WuP_Cyclic_Control = true;
						ETH2_Custom_Timing_WuP.setPhysicalRaw(250);
						setValueHWBuffer(false, ETH2_Custom_Timing_WuP);
						LOG(INFO) << "ETH2 WuP Cycletime set to 250";
					}
				}
			}
			else
			{
				if (WuP_Cyclic_Control)
				{
					ETH2_Custom_Timing_WuP.setPhysicalRaw(0);
					setValueHWBuffer(false, ETH2_Custom_Timing_WuP);
					WuP_Cyclic_Control = false;
				}
				ETH2_WuP_Init_Send_Count->quantity = none_t(0);
				ETH2_WuP_TimeSinceLastSend->quantity = none_t(0);
			}

			//ETH2_HB_PDU
			if (ETH2_HB_PDU_Used->quantity.get_value())
			{
				//if HB received from ECU (EBCM_ETH2_Init_HB_Received = true) HB CCU will be send on cyclic base
				if (CommonVars->EBCM_ETH2_Init_HB_Received->quantity.get_value() && ETH2_HB_TimeSinceLastSend->quantity.get_value() < cycleTimeHBTickCount)
				{
					ETH2_HB_TimeSinceLastSend->quantity += none_t(cycleTimer);
					if (ETH2_HB_TimeSinceLastSend->quantity.get_value() >= cycleTimeHBTickCount)
					{
						if (ETH2_HeartBeat_Counter->quantity.get_value() < 0xFFFFFFFF) ETH2_HeartBeat_Counter->quantity++;
						else ETH2_HeartBeat_Counter->quantity = none_t(0);
						ETH2_PDU_Heartbeat[12] = static_cast<uint8_t>((ETH2_HeartBeat_Counter->quantity.get_value() >> 24) & 0xFF);
						ETH2_PDU_Heartbeat[13] = static_cast<uint8_t>((ETH2_HeartBeat_Counter->quantity.get_value() >> 16) & 0xFF);
						ETH2_PDU_Heartbeat[14] = static_cast<uint8_t>((ETH2_HeartBeat_Counter->quantity.get_value() >> 8) & 0xFF);
						ETH2_PDU_Heartbeat[15] = static_cast<uint8_t>(ETH2_HeartBeat_Counter->quantity.get_value() & 0xFF);

						setValueHWBuffer(false, ETH2_PDU_Heartbeat);
						setValueHWBuffer(false, ETH2_Frame_Heartbeat);
						ETH2_HB_TimeSinceLastSend->quantity = none_t(0);
					}
				}
			}
			else
			{
				ETH2_HB_TimeSinceLastSend->quantity = none_t(0);
			}

			//ETH2_Info_PDU
			if (ETH2_Info_PDU_Used->quantity.get_value())
			{
				if (CommonVars->EBCM_ETH2_Init_HB_Received->quantity.get_value())
				{
					//we need to send info PDU for every 1 sec once until we get a +ve response from ECU
					if (!CommonVars->EBCM_ETH2_Info_Response_Received->quantity.get_value() && !CommonVars->EBCM_ETH2_Info_Response_Received->quantity.get_value()
						&& ETH2_Info_TimeSinceLastSend->quantity.get_value() < cycleTimeInfoTickCount)
					{
						ETH2_Info_TimeSinceLastSend->quantity += none_t(cycleTimer);
						if (ETH2_Info_TimeSinceLastSend->quantity.get_value() >= cycleTimeInfoTickCount)
						{
							ETH2_PDU_Info[24] = 0x01; //Info Activate bit enable

							setValueHWBuffer(false, ETH2_PDU_Info);
							setValueHWBuffer(false, ETH2_Frame_Info);
							ETH2_Info_TimeSinceLastSend->quantity = none_t(0);
							ETH2_Info_Activation->quantity = true;
						}
					}
					if (CommonVars->EBCM_ETH2_Info_Response_Received->quantity.get_value())
					{
						CommonVars->CCU_ETH2_Info_Activation_Status->quantity = true;
					}
				}
			}
			else
			{
				if (ETH2_Info_TimeSinceLastSend->quantity.get_value() < cycleTimeInfoTickCount && ETH2_Info_Activation->quantity.get_value())
				{
					ETH2_Info_TimeSinceLastSend->quantity += none_t(cycleTimer);
					if (ETH2_Info_TimeSinceLastSend->quantity.get_value() >= cycleTimeInfoTickCount)
					{
						ETH2_PDU_Info[24] = 0x02; //Info De-Activate bit enable

						setValueHWBuffer(false, ETH2_PDU_Info);
						setValueHWBuffer(false, ETH2_Frame_Info);

						ETH2_Info_TimeSinceLastSend->quantity = none_t(0);
						ETH2_Info_Activation->quantity = false;
						CommonVars->CCU_ETH2_Info_Activation_Status->quantity = false;
					}
				}
			}

			//ETH2_SomeIP
			if (CommonVars->CCU_ETH1_Info_Activation_Status->quantity.get_value() || CommonVars->CCU_ETH2_Info_Activation_Status->quantity.get_value())
			{
				if (!CommonVars->CCU_ETH2_SomeIP_Activation_Status->quantity.get_value() && ETH2_SomeIP_PDU_Used->quantity.get_value()
					&& ETH2_SomeIP_TimeSinceLastSend->quantity.get_value() < cycleTimeSomeIPTickCount)
				{
					ETH2_SomeIP_TimeSinceLastSend->quantity += none_t(cycleTimer);
					if (ETH2_SomeIP_TimeSinceLastSend->quantity.get_value() >= cycleTimeSomeIPTickCount)
					{
						gVarAlternativeTimingEth2.setPhysicalRaw(1);
						setValueHWBuffer(false, gVarAlternativeTimingEth2);

						CommonVars->CCU_ETH2_SomeIP_Activation_Status->quantity = true;
						ETH2_SomeIP_TimeSinceLastSend->quantity = none_t(0);
					}
				}
				else
				{
					if (CommonVars->CCU_ETH2_SomeIP_Activation_Status->quantity.get_value() && !ETH2_SomeIP_PDU_Used->quantity.get_value())
					{
						gVarAlternativeTimingEth2.setPhysicalRaw(0);
						setValueHWBuffer(false, gVarAlternativeTimingEth2);

						CommonVars->CCU_ETH2_SomeIP_Activation_Status->quantity = false;
					}
				}
			}
		}
	}
	else
	{
		Init = false;
		//WuP Reset
		ETH2_WuP_Init_Send_Count->quantity = none_t(0);
		ETH2_WuP_TimeSinceLastSend->quantity = none_t(0);

		//HeartBeat Reset
		ETH2_HB_TimeSinceLastSend->quantity = none_t(0);
		ETH2_HeartBeat_Counter->quantity = none_t(0);

		//Some IP and Info Reset
		ETH2_Info_TimeSinceLastSend->quantity = none_t(0);
		ETH2_SomeIP_TimeSinceLastSend->quantity = none_t(0);
		if (ETH2_Info_Activation->quantity.get_value())
		{
			ETH2_PDU_Info[24] = 0x02; //Info De-Activate bit enable

			setValueHWBuffer(false, ETH2_PDU_Info);
			setValueHWBuffer(false, ETH2_Frame_Info);

			CommonVars->CCU_ETH2_Info_Activation_Status->quantity = false;
			ETH2_Info_Activation->quantity = false;
		}
	}
	/*readSlot_Index = setValueHWBuffer(true, read_Index);

	if (readSlot_Index > 0)
	{
		success = pc_hw_interface_light->send_buffer(this->cardNumber, s_hwBuffer, readSlot_Index, wait);
	}*/
}