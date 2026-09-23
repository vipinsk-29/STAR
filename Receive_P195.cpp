/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.Receive_P140
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

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::Receive::P195(::model_core::common::time::SimulationTime* time_info)
{
	 using namespace model_core::quantity::literals;

     InitializeAllLists();

	 cycleTimer = globalPlugin.dt.get_value_in_unit<::model_core::quantity::time::Second>();
	 cycleTimerETH1_ReceivePDUCount = (double)Receive_ETH1_HB_PDU_CycleTimeTickCount->quantity.get_value() / ReceivePDU_CycleTimeDividend->quantity.get_value();
	 cycleTimerETH2_ReceivePDUCount = (double)Receive_ETH2_HB_PDU_CycleTimeTickCount->quantity.get_value() / ReceivePDU_CycleTimeDividend->quantity.get_value();
	 cycleTimer_Receive_ETH1_InfoPDUCount = (double)Receive_ETH1_InfoPDU_CycleTimeTickCount->quantity.get_value() / ReceivePDU_CycleTimeDividend->quantity.get_value();
	 cycleTimer_Receive_ETH2_InfoPDUCount = (double)Receive_ETH2_InfoPDU_CycleTimeTickCount->quantity.get_value() / ReceivePDU_CycleTimeDividend->quantity.get_value();
	 cycleTimer_ReceiveSignalCount = (double)Receive_CycleTimeTickCount->quantity.get_value() / Receive_CycleTimeDividend->quantity.get_value();
}