/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.MG_GM_BEV3_205_9p9_V01_M_P205
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
#include "Global/macros.h"
#include <g3log/g3log.hpp>
#include <g3log/loglevels.hpp>

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::MG_GM_BEV3_205_9p9_V01_M::P205(::model_core::common::time::SimulationTime* time_info)
{
	using namespace model_core::quantity::literals;

	wait = CommonVars->send_wait_ctrl->quantity.get_value();
	cycleTimer = globalPlugin.dt.get_value_in_unit<::model_core::quantity::time::Second>();

	// ─────────────────────────────────────────────────────────────────────────
	// STATE 1 — KL15 off / WuP not yet active  →  everything off, reset PDUs
	// ─────────────────────────────────────────────────────────────────────────
	if ((BatteryControl->UB_Ch3->quantity <= 3.0_V || !M2E->Driv_Ignition_sw->quantity.get_value())
		&& vl_Wup_State->quantity.get_value() == false)
	{
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
		LOG(INFO) << "STATE 1 — KL15 off / WuP not yet active  →  everything off, reset PDUs";

		vl_KL15_State->quantity = false;
		vl_Wup_State->quantity = true;
		vl_Ign_State->quantity = false;
		WuP_Reset_Inc->quantity = 0_none;
		Reset_Counter->quantity = 0_none;
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
	// ─────────────────────────────────────────────────────────────────────────
	// STATE 2 — KL15 rising edge  →  WuP pulse on, Ign off
	// ─────────────────────────────────────────────────────────────────────────
	else if (BatteryControl->UB_Ch3->quantity > 8.0_V
		&& M2E->Driv_Ignition_sw->quantity.get_value()
		&& vl_Ign_State->quantity.get_value() == false
		&& vl_Wup_State->quantity.get_value() == true)
	{
		gVarIgnitionState.setPhysicalRaw(0);
		gVarSetWuP.setPhysicalRaw(1);
		gVarAlternativeTimingEth1.setPhysicalRaw(0);
		gVarAlternativeTimingEth2.setPhysicalRaw(0);

		setValueHWBuffer(false, gVarIgnitionState);
		setValueHWBuffer(false, gVarSetWuP);
		setValueHWBuffer(false, gVarAlternativeTimingEth1);
		setValueHWBuffer(false, gVarAlternativeTimingEth2);
		LOG(INFO) << "STATE 2 — KL15 rising edge  →  WuP pulse on, Ign off";

		vl_KL15_State->quantity = false;
		vl_Wup_State->quantity = false;
		vl_Ign_State->quantity = true;
		WuP_Reset_Inc->quantity = 0_none;
		Reset_Counter->quantity = 0_none;
	}
	// ─────────────────────────────────────────────────────────────────────────
	// STATE 3 — WuP timer running  →  wait, then set Ign=1
	// ─────────────────────────────────────────────────────────────────────────
	else if (BatteryControl->UB_Ch3->quantity > 8.0_V
		&& M2E->Driv_Ignition_sw->quantity.get_value()
		&& vl_Ign_State->quantity.get_value() == true
		&& vl_Wup_State->quantity.get_value() == false
		&& WuP_Reset_Inc->quantity.get_value() < WuP_Reset_Counter->quantity.get_value())
	{
		WuP_Reset_Inc->quantity += none_t(cycleTimer);
		if (WuP_Reset_Inc->quantity.get_value() >= WuP_Reset_Counter->quantity.get_value())
		{
			gVarIgnitionState.setPhysicalRaw(1);
			gVarSetWuP.setPhysicalRaw(0);
			gVarAlternativeTimingEth1.setPhysicalRaw(0);
			gVarAlternativeTimingEth2.setPhysicalRaw(0);

			setValueHWBuffer(false, gVarIgnitionState);
			setValueHWBuffer(false, gVarSetWuP);
			setValueHWBuffer(false, gVarAlternativeTimingEth1);
			setValueHWBuffer(false, gVarAlternativeTimingEth2);
			LOG(INFO) << "STATE 3 — WuP timer running  →  wait, then set Ign=1";

			vl_KL15_State->quantity = true;
			vl_Wup_State->quantity = false;
			vl_Ign_State->quantity = false;
			WuP_Reset_Inc->quantity = 0_none;
			Reset_Counter->quantity = 0_none;
			CommonVars->TC10_Pulse_Status->quantity = true;
		}
	}
	else
	{
		// No action in this cycle
	}
	
	// ─────────────────────────────────────────────────────
	// GM-specific curve [CCU Mockup Unit]
	// ─────────────────────────────────────────────────────
	stroke->quantity = CommonVars->MS_stroke->quantity;
	p_tar_stroke->quantity = CurveStroke->curve.get_value_at(stroke->quantity);
	CommonVars->MS_p_tar_stroke->quantity = p_tar_stroke->quantity;

	// ─────────────────────────────────────────────────────
	// YRS Manipulation
	// ─────────────────────────────────────────────────────
	auto MS_Veh_vx_m_s = M2E->Vehicle_vx_m_s->quantity;
	auto MS_Veh_vy_m_s = M2E->Vehicle_vy_m_s->quantity;
	auto MS_Veh_vz_m_s = M2E->Vehicle_vz_m_s->quantity;
	auto MS_Veh_ax_m_s2 = M2E->Vehicle_ax_m_s2->quantity;
	auto MS_Veh_ay_m_s2 = M2E->Vehicle_ay_m_s2->quantity;
	auto MS_Veh_az_m_s2 = M2E->Vehicle_az_m_s2->quantity;
	auto MS_Veh_v_roll_deg_s = M2E->YRS_v_roll_deg_s->quantity;
	auto MS_Veh_v_pitch_deg_s = M2E->YRS_v_pitch_deg_s->quantity;
	auto MS_Veh_yawRate_deg_s = M2E->YRS_yawRate_deg_s->quantity;
	auto MS_Veh_a_roll_deg_s2 = M2E->YRS_a_roll_deg_s2->quantity;
	auto MS_Veh_a_pitch_deg_s2 = M2E->YRS_a_pitch_deg_s2->quantity;
	auto MS_Veh_a_yaw_deg_s2 = M2E->YRS_a_yaw_deg_s2->quantity;

	YrsTransformation.calc_sensorposition(
		CP_YRSPos_alpha_sim->quantity,
		CP_YRSPos_beta_sim->quantity,
		CP_YRSPos_gamma_sim->quantity,
		CP_YRSPos_x_sim->quantity,
		CP_YRSPos_y_sim->quantity,
		CP_YRSPos_z_sim->quantity);

	auto YrsReturnValues = YrsTransformation.calc_sensorsignals(
		MS_Veh_vx_m_s, MS_Veh_vy_m_s, MS_Veh_vz_m_s,
		MS_Veh_ax_m_s2, MS_Veh_ay_m_s2, MS_Veh_az_m_s2,
		MS_Veh_v_roll_deg_s, MS_Veh_v_pitch_deg_s, MS_Veh_yawRate_deg_s,
		MS_Veh_a_roll_deg_s2, MS_Veh_a_pitch_deg_s2, MS_Veh_a_yaw_deg_s2,
		CP_YRSPos_invertsign_x->quantity,
		CP_YRSPos_invertsign_y->quantity,
		::model_core::quantity::BooleanQuantity(false),
		::model_core::quantity::BooleanQuantity(false),
		::model_core::quantity::BooleanQuantity(false),
		CP_YRSPos_invertsign_yaw->quantity);

	CommonVars->MS_Veh_vx_m_s->quantity = YrsReturnValues->vx;
	CommonVars->MS_Veh_vy_m_s->quantity = YrsReturnValues->vy;
	CommonVars->MS_Veh_vz_m_s->quantity = YrsReturnValues->vz;
	CommonVars->MS2nd_Flx_Prot_A1S->quantity = YrsReturnValues->ax;
	CommonVars->MS2nd_Flx_Prot_A2S->quantity = YrsReturnValues->ay;
	CommonVars->MS2nd_Flx_Prot_A3S->quantity = YrsReturnValues->az;
	CommonVars->MS2nd_Flx_Prot_roll_deg_s->quantity = YrsReturnValues->rot_vx;
	CommonVars->MS2nd_Flx_Prot_pitch_deg_s->quantity = YrsReturnValues->rot_vy;
	CommonVars->MS2nd_Flx_Prot_yawRate->quantity = YrsReturnValues->rot_vz;
	CommonVars->MS_Veh_a_roll_deg_s2->quantity = YrsReturnValues->rot_ax;
	CommonVars->MS_Veh_a_pitch_deg_s2->quantity = YrsReturnValues->rot_ay;
	CommonVars->MS_Veh_a_yaw_deg_s2->quantity = YrsReturnValues->rot_az;


	/*if (readSlot_Index > 0)
	{
		success = pc_hw_interface_light->send_buffer(this->cardNumber, s_hwBuffer, readSlot_Index, wait);

		readSlot_Index = setValueHWBuffer(true, read_Index); // reset only after send
	}*/
}
