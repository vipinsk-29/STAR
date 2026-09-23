/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.ETH2_P360
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

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH2::P360(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;

	/*if (CommonVars->TC10_Pulse_Status->quantity == true)
	{
		//Mappings
		VeBACR_Pct_eBstAccelEffPosS__Sig->quantity = (none_t)M2E->Driv_AcceleratorPedal->quantity.get_value_in_unit<::model_core::quantity::ratio::Percent>();
		eth2VeBACR_Pct_eBstAccelEffPosS_Signal.setPhysicalRaw(VeBACR_Pct_eBstAccelEffPosS__Sig->quantity.get_value());

		VeBACR_e_eBstTransLvrPstnS__Sig->quantity = (none_t)M2E->Gears_Selector->quantity.get_value();
		eth2VeBACR_e_eBstTransLvrPstnS_Signal.setPhysicalRaw(VeBACR_e_eBstTransLvrPstnS__Sig->quantity.get_value());

		YeBACR_M_eBstTotAxlTrqActS__Sig->quantity = (none_t)M2E->Eng_IndTorq_NE_Nm->quantity.get_value_in_unit<::model_core::quantity::torque::Newtonmeter>();
		eth2YeBACR_M_eBstTotAxlTrqActS_Signal.setPhysicalRaw(YeBACR_M_eBstTotAxlTrqActS__Sig->quantity.get_value());

		//AC Pressure
		YeBACR_p_eBstBrkTgtLfS__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth2YeBACR_p_eBstBrkTgtLfS_Signal.setPhysicalRaw(YeBACR_p_eBstBrkTgtLfS__Sig->quantity.get_value());

		YeBACR_p_eBstBrkTgtRfS__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth2YeBACR_p_eBstBrkTgtRfS_Signal.setPhysicalRaw(YeBACR_p_eBstBrkTgtRfS__Sig->quantity.get_value());

		YeBACR_p_eBstBrkTgtLrS__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth2YeBACR_p_eBstBrkTgtLrS_Signal.setPhysicalRaw(YeBACR_p_eBstBrkTgtLrS__Sig->quantity.get_value());

		YeBACR_p_eBstBrkTgtRrS__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth2YeBACR_p_eBstBrkTgtRrS_Signal.setPhysicalRaw(YeBACR_p_eBstBrkTgtRrS__Sig->quantity.get_value());

		//SC Pressure
		VeBACR_p_eBstBkPrsTgtBaseS__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth2VeBACR_p_eBstBkPrsTgtBaseS_Signal.setPhysicalRaw(VeBACR_p_eBstBkPrsTgtBaseS__Sig->quantity.get_value());

		VeBACR_phi_eBstStrWhlAngS__Sig->quantity = (none_t)M2E->Driv_SteeringWheelAngle->quantity.get_value_in_unit<::model_core::quantity::angle::Degree>();
		eth2VeBACR_phi_eBstStrWhlAngS_Signal.setPhysicalRaw(VeBACR_phi_eBstStrWhlAngS__Sig->quantity.get_value());

		VeBACR_a_eBstVehAyS__Sig->quantity = (none_t)CommonVars->MS2nd_Flx_Prot_A2S->quantity.get_value_in_unit<::model_core::quantity::acceleration::MeterPerSquareSecond>();
		eth2VeBACR_a_eBstVehAyS_Signal.setPhysicalRaw(VeBACR_a_eBstVehAyS__Sig->quantity.get_value());

		// LinearVelocity = AngularVelocity * WheelRollingRadius;
		VeBACR_v_eBstWhlSpdLfS__Sig->quantity = static_cast<none_t>(M2E->Veh_omega_Wheel_FL_1_s->quantity.get_value_in_unit<::model_core::quantity::angular_velocity::RadianPerSecond>() * CommonVars->WHEEL_RADIUS->quantity);
		eth2VeBACR_v_eBstWhlSpdLfS_Signal.setPhysicalRaw(VeBACR_v_eBstWhlSpdLfS__Sig->quantity.get_value());

		VeBACR_v_eBstWhlSpdRfS__Sig->quantity = static_cast<none_t>(M2E->Veh_omega_Wheel_FR_1_s->quantity.get_value_in_unit<::model_core::quantity::angular_velocity::RadianPerSecond>() * CommonVars->WHEEL_RADIUS->quantity);
		eth2VeBACR_v_eBstWhlSpdRfS_Signal.setPhysicalRaw(VeBACR_v_eBstWhlSpdRfS__Sig->quantity.get_value());

		VeBACR_v_eBstWhlSpdLrS__Sig->quantity = static_cast<none_t>(M2E->Veh_omega_Wheel_RL_1_s->quantity.get_value_in_unit<::model_core::quantity::angular_velocity::RadianPerSecond>() * CommonVars->WHEEL_RADIUS->quantity);
		eth2VeBACR_v_eBstWhlSpdLrS_Signal.setPhysicalRaw(VeBACR_v_eBstWhlSpdLrS__Sig->quantity.get_value());

		VeBACR_v_eBstWhlSpdRrS__Sig->quantity = static_cast<none_t>(M2E->Veh_omega_Wheel_RR_1_s->quantity.get_value_in_unit<::model_core::quantity::angular_velocity::RadianPerSecond>() * CommonVars->WHEEL_RADIUS->quantity);
		eth2VeBACR_v_eBstWhlSpdRrS_Signal.setPhysicalRaw(VeBACR_v_eBstWhlSpdRrS__Sig->quantity.get_value());

		YeBACR_e_eBstBrkOprtnRqstS__Sig->quantity = 1_none;
		eth2YeBACR_e_eBstBrkOprtnRqstS_Signal.setPhysicalRaw(YeBACR_e_eBstBrkOprtnRqstS__Sig->quantity.get_value());

		YeBACR_e_eBstHydFuncStCmdS__Sig->quantity = 1_none;
		eth2YeBACR_e_eBstHydFuncStCmdS_Signal.setPhysicalRaw(YeBACR_e_eBstHydFuncStCmdS__Sig->quantity.get_value());

		//Ignition ON = VeBACR_b_PropSysActvP ->1 & VeBACR_e_eBstPriPwrModeP -> 2
		VeBACR_b_PropSysActvS__Sig->quantity = 1_none;
		eth2VeBACR_b_PropSysActvS_Signal.setPhysicalRaw(VeBACR_b_PropSysActvS__Sig->quantity.get_value());

		VeBACR_e_eBstPriPwrModeS__Sig->quantity = 2_none;
		eth2VeBACR_e_eBstPriPwrModeS_Signal.setPhysicalRaw(VeBACR_e_eBstPriPwrModeS__Sig->quantity.get_value());
	}
	else
	{
		//Ignition ON = VeBACR_b_PropSysActvP ->0 & VeBACR_e_eBstPriPwrModeP -> 0
		VeBACR_b_PropSysActvS__Sig->quantity = 0_none;
		eth2VeBACR_b_PropSysActvS_Signal.setPhysicalRaw(VeBACR_b_PropSysActvS__Sig->quantity.get_value());

		VeBACR_e_eBstPriPwrModeS__Sig->quantity = 0_none;
		eth2VeBACR_e_eBstPriPwrModeS_Signal.setPhysicalRaw(VeBACR_e_eBstPriPwrModeS__Sig->quantity.get_value());

		YeBACR_e_eBstBrkOprtnRqstS__Sig->quantity = 0_none;
		eth2YeBACR_e_eBstBrkOprtnRqstS_Signal.setPhysicalRaw(YeBACR_e_eBstBrkOprtnRqstS__Sig->quantity.get_value());

		YeBACR_e_eBstHydFuncStCmdS__Sig->quantity = 0_none;
		eth2YeBACR_e_eBstHydFuncStCmdS_Signal.setPhysicalRaw(YeBACR_e_eBstHydFuncStCmdS__Sig->quantity.get_value());
	}*/
}