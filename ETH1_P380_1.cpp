/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.ETH1_P380_1
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

#include "../ETH1.h"
#include "ModelCore/Quantity/Literals.h"
using namespace Plugins::FlexCard3::PC_HW_Interface::Light;

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1::P380_1(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;
	wait = CommonVars->send_wait_ctrl->quantity.get_value();

	// Check if TC10_Pulse_Status is true
	if (CommonVars->TC10_Pulse_Status->quantity.get_value())
	{
		//ETH1_Node_Used is true (Normal Operation)
		if (ETH1_Node_Used->quantity.get_value())
		{
			if (!Init)
			{
				//from P195
				ETH1_PDU_WuP.setRaw(setRawPduWakeUpBuffer_V22.data(), CommonVars->CCU_ETH1_WuP_PDU_Length->quantity.get_value());
				setValueHWBuffer(false, ETH1_PDU_WuP);
				setValueHWBuffer(false, ETH1_Frame_WuP);

				ETH1_PDU_Heartbeat.setRaw(setRawPduHBBuffer_V22.data(), CommonVars->CCU_ETH1_HB_PDU_Length->quantity.get_value());
				setValueHWBuffer(false, ETH1_PDU_Heartbeat);
				setValueHWBuffer(false, ETH1_Frame_Heartbeat);

				ETH1_PDU_Info.setRaw(setRawPduInfoBuffer_V22.data(), 28); // CommonVars->CCU_ETH1_Info_PDU_Length->quantity.get_value());
				setValueHWBuffer(false, ETH1_PDU_Info);
				setValueHWBuffer(false, ETH1_Frame_Info);

				if (ETH1_WuP_Init_Send_Count->quantity == 0_none)
				{
					WuP_Cyclic_Control = false;
					ETH1_Custom_Timing_WuP.setPhysicalRaw(10);
					setValueHWBuffer(false, ETH1_Custom_Timing_WuP);
					LOG(INFO) << "ETH1 WuP Cycletime set to 10";
				}
				Init = true;
			}
			//ETH1_WuP_PDU
			if (ETH1_WuP_PDU_Used->quantity.get_value())
			{
				//WuP Init PDU will be sent for ETH2_WuP_Init_Send_Max times with 10mS interval, 
				if (ETH1_WuP_Init_Send_Count->quantity.get_value() < ETH1_WuP_Init_Send_Max->quantity.get_value())
				{
					if (ETH1_WuP_TimeSinceLastSend->quantity.get_value() < cycleTimeWuPInitTickCount)
					{
						ETH1_WuP_TimeSinceLastSend->quantity += none_t(cycleTimer);
						if (ETH1_WuP_TimeSinceLastSend->quantity.get_value() >= cycleTimeWuPInitTickCount)
						{
							ETH1_WuP_TimeSinceLastSend->quantity = none_t(0);
							ETH1_WuP_Init_Send_Count->quantity++;
						}
					}
				}
				else
				{
					if (ETH1_WuP_Init_Send_Count->quantity.get_value() >= ETH1_WuP_Init_Send_Max->quantity.get_value() && !WuP_Cyclic_Control)
					{
						WuP_Cyclic_Control = true;
						ETH1_Custom_Timing_WuP.setPhysicalRaw(250);
						setValueHWBuffer(false, ETH1_Custom_Timing_WuP);
						LOG(INFO) << "ETH1 WuP Cycletime set to 250";
					}
				}
			}
			else
			{
				if (WuP_Cyclic_Control)
				{
					ETH1_Custom_Timing_WuP.setPhysicalRaw(0);
					setValueHWBuffer(false, ETH1_Custom_Timing_WuP);
					WuP_Cyclic_Control = false;
				}
				ETH1_WuP_Init_Send_Count->quantity = none_t(0);
				ETH1_WuP_TimeSinceLastSend->quantity = none_t(0);
			}

			//ETH1_HB_PDU
			if (ETH1_HB_PDU_Used->quantity.get_value())
			{
				//if HB received from ECU (EBCM_ETH1_Init_HB_Received = true) HB CCU will be send on cyclic base
				if (CommonVars->EBCM_ETH1_Init_HB_Received->quantity.get_value() && ETH1_HB_TimeSinceLastSend->quantity.get_value() < cycleTimeHBTickCount)
				{
					ETH1_HB_TimeSinceLastSend->quantity += none_t(cycleTimer);
					if (ETH1_HB_TimeSinceLastSend->quantity.get_value() >= cycleTimeHBTickCount)
					{
						if (ETH1_HeartBeat_Counter->quantity.get_value() < 0xFFFFFFFF) ETH1_HeartBeat_Counter->quantity++;
						else ETH1_HeartBeat_Counter->quantity = none_t(0);
						ETH1_PDU_Heartbeat[12] = static_cast<uint8_t>((ETH1_HeartBeat_Counter->quantity.get_value() >> 24) & 0xFF);
						ETH1_PDU_Heartbeat[13] = static_cast<uint8_t>((ETH1_HeartBeat_Counter->quantity.get_value() >> 16) & 0xFF);
						ETH1_PDU_Heartbeat[14] = static_cast<uint8_t>((ETH1_HeartBeat_Counter->quantity.get_value() >> 8) & 0xFF);
						ETH1_PDU_Heartbeat[15] = static_cast<uint8_t>(ETH1_HeartBeat_Counter->quantity.get_value() & 0xFF);

						setValueHWBuffer(false, ETH1_PDU_Heartbeat);
						setValueHWBuffer(false, ETH1_Frame_Heartbeat);
						ETH1_HB_TimeSinceLastSend->quantity = none_t(0);
					}
				}
			}
			else
			{
				ETH1_HB_TimeSinceLastSend->quantity = none_t(0);
			}

			//ETH1_Info_PDU
			if (ETH1_Info_PDU_Used->quantity.get_value())
			{
				if (CommonVars->EBCM_ETH1_Init_HB_Received->quantity.get_value())
				{
					//we need to send info PDU for every 1 sec once until we get a +ve response from ECU
					if (!CommonVars->EBCM_ETH1_Info_Response_Received->quantity.get_value() && !CommonVars->EBCM_ETH2_Info_Response_Received->quantity.get_value()
						&& ETH1_Info_TimeSinceLastSend->quantity.get_value() < cycleTimeInfoTickCount)
					{
						ETH1_Info_TimeSinceLastSend->quantity += none_t(cycleTimer);
						if (ETH1_Info_TimeSinceLastSend->quantity.get_value() >= cycleTimeInfoTickCount)
						{
							ETH1_PDU_Info[24] = 0x01; //Info Activate bit enable

							setValueHWBuffer(false, ETH1_PDU_Info);
							setValueHWBuffer(false, ETH1_Frame_Info);
							ETH1_Info_TimeSinceLastSend->quantity = none_t(0);
							ETH1_Info_Activation->quantity = true;
						}
					}
					if (CommonVars->EBCM_ETH1_Info_Response_Received->quantity.get_value())
					{
						CommonVars->CCU_ETH1_Info_Activation_Status->quantity = true;
					}
				}
			}
			else
			{
				if (ETH1_Info_TimeSinceLastSend->quantity.get_value() < cycleTimeInfoTickCount && ETH1_Info_Activation->quantity.get_value())
				{
					ETH1_Info_TimeSinceLastSend->quantity += none_t(cycleTimer);
					if (ETH1_Info_TimeSinceLastSend->quantity.get_value() >= cycleTimeInfoTickCount)
					{
						ETH1_PDU_Info[24] = 0x02; //Info De-Activate bit enable

						setValueHWBuffer(false, ETH1_PDU_Info);
						setValueHWBuffer(false, ETH1_Frame_Info);

						ETH1_Info_TimeSinceLastSend->quantity = none_t(0);
						ETH1_Info_Activation->quantity = false;
						CommonVars->CCU_ETH1_Info_Activation_Status->quantity = false;
					}
				}
			}

			//ETH1_SomeIP
			if (CommonVars->CCU_ETH1_Info_Activation_Status->quantity.get_value() || CommonVars->CCU_ETH2_Info_Activation_Status->quantity.get_value())
			{
				if (!CommonVars->CCU_ETH1_SomeIP_Activation_Status->quantity.get_value() && !CommonVars->CCU_ETH2_SomeIP_Activation_Status->quantity.get_value() &&
					ETH1_SomeIP_TimeSinceLastSend->quantity.get_value() < cycleTimeSomeIPTickCount)
				{
					ETH1_SomeIP_TimeSinceLastSend->quantity += none_t(cycleTimer);
					if (ETH1_SomeIP_TimeSinceLastSend->quantity.get_value() >= cycleTimeSomeIPTickCount)
					{
						gVarAlternativeTimingEth1.setPhysicalRaw(1);
						setValueHWBuffer(false, gVarAlternativeTimingEth1);

						gVarAlternativeTimingEth2.setPhysicalRaw(1);
						setValueHWBuffer(false, gVarAlternativeTimingEth2);

						CommonVars->CCU_ETH1_SomeIP_Activation_Status->quantity = true;
						CommonVars->CCU_ETH2_SomeIP_Activation_Status->quantity = true;
						ETH1_SomeIP_TimeSinceLastSend->quantity = none_t(0);
					}
				}
				else if (!CommonVars->CCU_ETH1_SomeIP_Activation_Status->quantity.get_value() && ETH1_SomeIP_PDU_Used->quantity.get_value()
					&& ETH1_SomeIP_TimeSinceLastSend->quantity.get_value() < cycleTimeSomeIPTickCount)
				{
					ETH1_SomeIP_TimeSinceLastSend->quantity += none_t(cycleTimer);
					if (ETH1_SomeIP_TimeSinceLastSend->quantity.get_value() >= cycleTimeSomeIPTickCount)
					{
						gVarAlternativeTimingEth1.setPhysicalRaw(1);
						setValueHWBuffer(false, gVarAlternativeTimingEth1);

						CommonVars->CCU_ETH1_SomeIP_Activation_Status->quantity = true;
						ETH1_SomeIP_TimeSinceLastSend->quantity = none_t(0);
					}
				}
				else
				{
					if (CommonVars->CCU_ETH1_SomeIP_Activation_Status->quantity.get_value() && !ETH1_SomeIP_PDU_Used->quantity.get_value())
					{
						gVarAlternativeTimingEth1.setPhysicalRaw(0);
						setValueHWBuffer(false, gVarAlternativeTimingEth1);

						CommonVars->CCU_ETH1_SomeIP_Activation_Status->quantity = false;
					}
				}
			}
		}
	}
	else
	{
		Init = false;

		//WuP Reset
		ETH1_WuP_Init_Send_Count->quantity = none_t(0);
		ETH1_WuP_TimeSinceLastSend->quantity = none_t(0);

		//HeartBeat Reset
		ETH1_HB_TimeSinceLastSend->quantity = none_t(0);
		ETH1_HeartBeat_Counter->quantity = none_t(0);

		//Some IP and Info Reset
		ETH1_Info_TimeSinceLastSend->quantity = none_t(0);
		ETH1_SomeIP_TimeSinceLastSend->quantity = none_t(0);
		if (ETH1_Info_Activation->quantity.get_value())
		{
			ETH1_PDU_Info[24] = 0x02; //Info De-Activate bit enable

			setValueHWBuffer(false, ETH1_PDU_Info);
			setValueHWBuffer(false, ETH1_Frame_Info);

			CommonVars->CCU_ETH1_Info_Activation_Status->quantity = false;
			ETH1_Info_Activation->quantity = false;
		}
	}
	//readSlot_Index = setValueHWBuffer(true, read_Index);

	/*if (readSlot_Index > 0)
	{
		success = pc_hw_interface_light->send_buffer(this->cardNumber, s_hwBuffer, readSlot_Index, wait);
	}*/
}