/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.MG_GM_BEV3_205_9p9_V01_M_P400
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

#include "../MG_GM_BEV3_205_9p9_V01_M.h"
#include "ModelCore/Quantity/Literals.h"

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::MG_GM_BEV3_205_9p9_V01_M::P400(::model_core::common::time::SimulationTime* time_info)
{
		// ToDo: implement process
	using namespace model_core::quantity::literals;

	// Set physical values
	gVarIgnitionState.setPhysicalRaw(0);
	gVarSetWuP.setPhysicalRaw(0);
	gVarAlternativeTimingEth1.setPhysicalRaw(0);
	gVarAlternativeTimingEth2.setPhysicalRaw(0);

	// Fill HW send buffer
	setValueHWBuffer(false, gVarIgnitionState);
	setValueHWBuffer(false, gVarSetWuP);
	setValueHWBuffer(false, gVarAlternativeTimingEth1);
	setValueHWBuffer(false, gVarAlternativeTimingEth2);

	vl_KL15_State->quantity = false;
	vl_Ign_State->quantity = false;
	vl_Wup_State->quantity = false;
	WuP_Reset_Inc->quantity = 0_none;
	CommonVars->TC10_Pulse_Status->quantity = false;
	CommonVars->EBCM_ETH1_Init_HB_Received->quantity = false;
	CommonVars->EBCM_ETH1_Cyclic_HB_Received->quantity = false;
	CommonVars->EBCM_ETH1_Info_Response_Received->quantity = false;
	CommonVars->CCU_ETH1_Info_Activation_Status->quantity = false;
	CommonVars->CCU_ETH1_SomeIP_Activation_Status->quantity = false;
	CommonVars->EBCM_ETH2_Init_HB_Received->quantity = false;
	CommonVars->EBCM_ETH2_Cyclic_HB_Received->quantity = false;
	CommonVars->EBCM_ETH2_Info_Response_Received->quantity = false;
	CommonVars->CCU_ETH2_Info_Activation_Status->quantity = false;
	CommonVars->CCU_ETH2_SomeIP_Activation_Status->quantity = false;
}