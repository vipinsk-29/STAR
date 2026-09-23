/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.ETH1_P360
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

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1::P360(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;

	/*if (CommonVars->TC10_Pulse_Status->quantity == true)
	{
		//Mappings
		VeBACR_Pct_eBstAccelEffPosP__Sig->quantity = (none_t)M2E->Driv_AcceleratorPedal->quantity.get_value_in_unit<::model_core::quantity::ratio::Percent>();
		eth1VeBACR_Pct_eBstAccelEffPosP_Signal.setPhysicalRaw(VeBACR_Pct_eBstAccelEffPosP__Sig->quantity.get_value());

		VeBACR_e_eBstTransLvrPstnP__Sig->quantity = (none_t)M2E->Gears_Selector->quantity.get_value();
		eth1VeBACR_e_eBstTransLvrPstnP_Signal.setPhysicalRaw(VeBACR_e_eBstTransLvrPstnP__Sig->quantity.get_value());

		YeBACR_M_eBstTotAxlTrqActP__Sig->quantity = (none_t)M2E->Eng_IndTorq_NE_Nm->quantity.get_value_in_unit<::model_core::quantity::torque::Newtonmeter>();
		eth1YeBACR_M_eBstTotAxlTrqActP_Signal.setPhysicalRaw(YeBACR_M_eBstTotAxlTrqActP__Sig->quantity.get_value());

		//AC Pressure
		YeBACR_p_eBstBrkTgtLfP__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth1YeBACR_p_eBstBrkTgtLfP_Signal.setPhysicalRaw(YeBACR_p_eBstBrkTgtLfP__Sig->quantity.get_value());

		YeBACR_p_eBstBrkTgtRfP__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth1YeBACR_p_eBstBrkTgtRfP_Signal.setPhysicalRaw(YeBACR_p_eBstBrkTgtRfP__Sig->quantity.get_value());

		YeBACR_p_eBstBrkTgtLrP__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth1YeBACR_p_eBstBrkTgtLrP_Signal.setPhysicalRaw(YeBACR_p_eBstBrkTgtLrP__Sig->quantity.get_value());

		YeBACR_p_eBstBrkTgtRrP__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth1YeBACR_p_eBstBrkTgtRrP_Signal.setPhysicalRaw(YeBACR_p_eBstBrkTgtRrP__Sig->quantity.get_value());

		//SC Pressure
		VeBACR_p_eBstBkPrsTgtBaseP__Sig->quantity = (none_t)(CommonVars->MS_p_tar_stroke->quantity.get_value() / 100000);
		eth1VeBACR_p_eBstBkPrsTgtBaseP_Signal.setPhysicalRaw(VeBACR_p_eBstBkPrsTgtBaseP__Sig->quantity.get_value());

		VeBACR_phi_eBstStrWhlAngP__Sig->quantity = (none_t)M2E->Driv_SteeringWheelAngle->quantity.get_value_in_unit<::model_core::quantity::angle::Degree>();
		eth1VeBACR_phi_eBstStrWhlAngP_Signal.setPhysicalRaw(VeBACR_phi_eBstStrWhlAngP__Sig->quantity.get_value());

		VeBACR_a_eBstVehAyP__Sig->quantity = (none_t)CommonVars->MS2nd_Flx_Prot_A2S->quantity.get_value_in_unit<::model_core::quantity::acceleration::MeterPerSquareSecond>();
		eth1VeBACR_a_eBstVehAyP_Signal.setPhysicalRaw(VeBACR_a_eBstVehAyP__Sig->quantity.get_value());

		// LinearVelocity = AngularVelocity * WheelRollingRadius;
		VeBACR_v_eBstWhlSpdLfP__Sig->quantity = static_cast<none_t>(M2E->Veh_omega_Wheel_FL_1_s->quantity.get_value_in_unit<::model_core::quantity::angular_velocity::RadianPerSecond>() * CommonVars->WHEEL_RADIUS->quantity);
		eth1VeBACR_v_eBstWhlSpdLfP_Signal.setPhysicalRaw(VeBACR_v_eBstWhlSpdLfP__Sig->quantity.get_value());

		VeBACR_v_eBstWhlSpdRfP__Sig->quantity = static_cast<none_t>(M2E->Veh_omega_Wheel_FR_1_s->quantity.get_value_in_unit<::model_core::quantity::angular_velocity::RadianPerSecond>() * CommonVars->WHEEL_RADIUS->quantity);
		eth1VeBACR_v_eBstWhlSpdRfP_Signal.setPhysicalRaw(VeBACR_v_eBstWhlSpdRfP__Sig->quantity.get_value());

		VeBACR_v_eBstWhlSpdLrP__Sig->quantity = static_cast<none_t>(M2E->Veh_omega_Wheel_RL_1_s->quantity.get_value_in_unit<::model_core::quantity::angular_velocity::RadianPerSecond>() * CommonVars->WHEEL_RADIUS->quantity);
		eth1VeBACR_v_eBstWhlSpdLrP_Signal.setPhysicalRaw(VeBACR_v_eBstWhlSpdLrP__Sig->quantity.get_value());

		VeBACR_v_eBstWhlSpdRrP__Sig->quantity = static_cast<none_t>(M2E->Veh_omega_Wheel_RR_1_s->quantity.get_value_in_unit<::model_core::quantity::angular_velocity::RadianPerSecond>() * CommonVars->WHEEL_RADIUS->quantity);
		eth1VeBACR_v_eBstWhlSpdRrP_Signal.setPhysicalRaw(VeBACR_v_eBstWhlSpdRrP__Sig->quantity.get_value());

		YeBACR_e_eBstBrkOprtnRqstP__Sig->quantity = 1_none;
		eth1YeBACR_e_eBstBrkOprtnRqstP_Signal.setPhysicalRaw(YeBACR_e_eBstBrkOprtnRqstP__Sig->quantity.get_value());

		YeBACR_e_eBstHydFuncStCmdP__Sig->quantity = 1_none;
		eth1YeBACR_e_eBstHydFuncStCmdP_Signal.setPhysicalRaw(YeBACR_e_eBstHydFuncStCmdP__Sig->quantity.get_value());

		//Ignition ON = VeBACR_b_PropSysActvP ->1 & VeBACR_e_eBstPriPwrModeP -> 2
		VeBACR_b_PropSysActvP__Sig->quantity = 1_none;
		eth1VeBACR_b_PropSysActvP_Signal.setPhysicalRaw(VeBACR_b_PropSysActvP__Sig->quantity.get_value());

		VeBACR_e_eBstPriPwrModeP__Sig->quantity = 2_none;
		eth1VeBACR_e_eBstPriPwrModeP_Signal.setPhysicalRaw(VeBACR_e_eBstPriPwrModeP__Sig->quantity.get_value());
	}
	else
	{
		//Ignition OFF = VeBACR_b_PropSysActvP ->0 & VeBACR_e_eBstPriPwrModeP -> 0
		VeBACR_b_PropSysActvP__Sig->quantity = 0_none;
		eth1VeBACR_b_PropSysActvP_Signal.setPhysicalRaw(VeBACR_b_PropSysActvP__Sig->quantity.get_value());

		VeBACR_e_eBstPriPwrModeP__Sig->quantity = 0_none;
		eth1VeBACR_e_eBstPriPwrModeP_Signal.setPhysicalRaw(VeBACR_e_eBstPriPwrModeP__Sig->quantity.get_value());

		YeBACR_e_eBstBrkOprtnRqstP__Sig->quantity = 0_none;
		eth1YeBACR_e_eBstBrkOprtnRqstP_Signal.setPhysicalRaw(YeBACR_e_eBstBrkOprtnRqstP__Sig->quantity.get_value());

		YeBACR_e_eBstHydFuncStCmdP__Sig->quantity = 0_none;
		eth1YeBACR_e_eBstHydFuncStCmdP_Signal.setPhysicalRaw(YeBACR_e_eBstHydFuncStCmdP__Sig->quantity.get_value());
	}*/
}