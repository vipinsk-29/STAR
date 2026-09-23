/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.ETH1
/* SW-COMPONENT: C++-genericToolChainModelComponent
/* DESCRIPTION: Source is used to build a Labcar model component for a generic ToolChain, based on C++ code
/* COPYRIGHT: (C) 2025 Robert Bosch GmbH
/******************************************************************/

#include "ETH1Core.h"
#include "Defs/ModelData.h"

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1Core::initialize()
{
	const std::string moduleName = this->get_component_description().get_module_name();
	const auto found = moduleName.find_last_of('.');
	nodeName = moduleName.substr(found + 1);

	moduloSignalList.clear();
	for (::model_core::model::Signal* moduloSignal : this->get_signals())
	{
		moduloSignalList.insert(std::make_pair(moduloSignal->get_name(), moduloSignal));
	}
}

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1Core::uninitialize()
{
	FloatSigManipulationHelperList.clear();
	eth1OldPhysValueMap.clear();
	eth1HwSignalMap.clear();
}

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1Core::InitializeAllLists()
{
	pc_hw_int = PC_HW_Int_Client->getPcHwIntLibVersion();
	pc_hw_interface_light = PC_HW_Int_Lt_Client->getPcHwIntLightVersion();

	SignalListData();
	PDUListData();
	FRAMEListData();
	GlobalVars_list();
	FloatSigManipulationHelperList.clear();
}

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1Core::SignalListData()
{
	auto signals_xml = helper->Get_readxml()->GetSetSignalList(nodeName.c_str());

	std::unordered_map<std::string, std::reference_wrapper<decltype(eth1VeBACR_b_eBstTransSIP_Signal)>> m
	{
		{"VeBACR_b_eBstTransSIP_P",        eth1VeBACR_b_eBstTransSIP_Signal},
		{"YeBACR_M_eBstTotAxlTrqActP",     eth1YeBACR_M_eBstTotAxlTrqActP_Signal},
		{"VeBACR_b_eBstFuncTstAllwdP",     eth1VeBACR_b_eBstFuncTstAllwdP_Signal},
		{"YeBACR_p_eBstBrkTgtRrP",         eth1YeBACR_p_eBstBrkTgtRrP_Signal},
		{"VeBACR_phi_eBstStrWhlAngP",      eth1VeBACR_phi_eBstStrWhlAngP_Signal},
		{"YeBACR_e_eBstActrModeRfP",       eth1YeBACR_e_eBstActrModeRfP_Signal},
		{"YeBACR_e_eBstBrkCmdTypeLfP",     eth1YeBACR_e_eBstBrkCmdTypeLfP_Signal},
		{"VeBACR_b_eBstOAT_InvP",          eth1VeBACR_b_eBstOAT_InvP_Signal},
		{"VeBACR_v_eBstWhlSpdRfP",         eth1VeBACR_v_eBstWhlSpdRfP_Signal},
		{"YeBACR_I_eBstPwrMgmtSinkLimP",   eth1YeBACR_I_eBstPwrMgmtSinkLimP_Signal},
		{"VeBACR_b_eBstWhlSpdLfInvP",      eth1VeBACR_b_eBstWhlSpdLfInvP_Signal},
		{"VeBACR_a_eBstVehAyP",            eth1VeBACR_a_eBstVehAyP_Signal},
		{"YeBACR_p_eBstBrkTgtLfP",         eth1YeBACR_p_eBstBrkTgtLfP_Signal},
		{"VeBACR_b_eBstRmtPrgActvP",       eth1VeBACR_b_eBstRmtPrgActvP_Signal},
		{"VeBACR_T_eBstOAT_CorrP",         eth1VeBACR_T_eBstOAT_CorrP_Signal},
		{"YeBACR_e_eBstBrkCmdTypeRrP",     eth1YeBACR_e_eBstBrkCmdTypeRrP_Signal},
		{"YeBACR_p_eBstBrkTgtRfP",         eth1YeBACR_p_eBstBrkTgtRfP_Signal},
		{"YeBACR_I_eBstPwrMgmtGenLimP",    eth1YeBACR_I_eBstPwrMgmtGenLimP_Signal},
		{"YeBACR_e_eBstActrModeLfP",       eth1YeBACR_e_eBstActrModeLfP_Signal},
		{"VeBACR_v_eBstWhlSpdLfP",         eth1VeBACR_v_eBstWhlSpdLfP_Signal},
		{"VeBACR_v_eBstWhlSpdRrP",         eth1VeBACR_v_eBstWhlSpdRrP_Signal},
		{"VeBACR_e_eBstEPB_CmdP",          eth1VeBACR_e_eBstEPB_CmdP_Signal},
		{"VeBACR_F_eBstEPB_StateCmdLtP",   eth1VeBACR_F_eBstEPB_StateCmdLtP_Signal},
		{"VeBACR_e_eBstBrkSysPwrModeP",    eth1VeBACR_e_eBstBrkSysPwrModeP_Signal},
		{"YeBACR_e_eBstActrModeLrP",       eth1YeBACR_e_eBstActrModeLrP_Signal},
		{"YeBACR_e_eBstHydFuncStCmdP",     eth1YeBACR_e_eBstHydFuncStCmdP_Signal},
		{"YeBACR_b_eBstPwrMgmtReqP",       eth1YeBACR_b_eBstPwrMgmtReqP_Signal},
		{"VeBACR_Pct_eBstAccelEffPosP",    eth1VeBACR_Pct_eBstAccelEffPosP_Signal},
		{"YeBACR_a_eBstVeh_AxP",           eth1YeBACR_a_eBstVeh_AxP_Signal},
		{"VeBACR_F_eBstEPB_StateCmdRtP",   eth1VeBACR_F_eBstEPB_StateCmdRtP_Signal},
		{"VeBACR_b_eBstWhlSpdRrInvP",      eth1VeBACR_b_eBstWhlSpdRrInvP_Signal},
		{"YeBACR_e_eBstActrModeRrP",       eth1YeBACR_e_eBstActrModeRrP_Signal},
		{"VeBACR_b_eBstWhlSpdRfInvP",      eth1VeBACR_b_eBstWhlSpdRfInvP_Signal},
		{"VeBACR_b_eBstVeh_AxInvP",        eth1VeBACR_b_eBstVeh_AxInvP_Signal},
		{"VeBACR_l_eBstVehOdoBCM_P",       eth1VeBACR_l_eBstVehOdoBCM_P_Signal},
		{"YeBACR_e_eBstBrkCmdTypeRfP",     eth1YeBACR_e_eBstBrkCmdTypeRfP_Signal},
		{"VeBACR_b_eBstWhlSpdLrInvP",      eth1VeBACR_b_eBstWhlSpdLrInvP_Signal},
		{"YeBACR_e_eBstBrkCmdTypeLrP",     eth1YeBACR_e_eBstBrkCmdTypeLrP_Signal},
		{"VeBACR_v_eBstWhlSpdLrP",         eth1VeBACR_v_eBstWhlSpdLrP_Signal},
		{"YeBACR_p_eBstBrkTgtLrP",         eth1YeBACR_p_eBstBrkTgtLrP_Signal},
		{"VeBACR_e_eBstTransLvrPstnP",     eth1VeBACR_e_eBstTransLvrPstnP_Signal},
		{"VeBACR_b_eBstWrmUpCyclCmptP",    eth1VeBACR_b_eBstWrmUpCyclCmptP_Signal},
		{"VeBACR_b_eBstRnCrnkActBkupP",    eth1VeBACR_b_eBstRnCrnkActBkupP_Signal},
		{"VeBACR_e_eBstPriPwrModeP",       eth1VeBACR_e_eBstPriPwrModeP_Signal},
		{"VeBACR_b_eBstRnCrnkActPriP",     eth1VeBACR_b_eBstRnCrnkActPriP_Signal},
		{"VeBACR_e_eBstBkupPwrModeP",      eth1VeBACR_e_eBstBkupPwrModeP_Signal},
		{"VeBACR_y_eBstVehRegionCodeP",    eth1VeBACR_y_eBstVehRegionCodeP_Signal},
		{"VeBACR_b_PropSysActvP",          eth1VeBACR_b_PropSysActvP_Signal},
		{"VeBACR_v_eBstVehicleP",          eth1VeBACR_v_eBstVehicleP_Signal},
		{"VeBACR_V_eBstRplnshVolTrgtP",    eth1VeBACR_V_eBstRplnshVolTrgtP_Signal},
		{"VeBACR_p_eBstBkPrsTgtBaseP",     eth1VeBACR_p_eBstBkPrsTgtBaseP_Signal},
		{"SSMR_0C598001_0CD68001_QoS",     eth1SSMR_0C598001_0CD68001_QoS_Signal},
		{"YeBACR_e_eBstBrkOprtnRqstP",     eth1YeBACR_e_eBstBrkOprtnRqstP_Signal},
		{"NeBACR_b_eBstBrkFdSt2DiagP",     eth1NeBACR_b_eBstBrkFdSt2DiagP_Signal},
		{"NeBACR_t_eBstPropSysInactvP",    eth1NeBACR_t_eBstPropSysInactvP_Signal},
		{"VeBACR_b_eBstEPB_HpoAvailP",     eth1VeBACR_b_eBstEPB_HpoAvailP_Signal},
		{"VeBACR_e_eBstRplnshTriggerP",    eth1VeBACR_e_eBstRplnshTriggerP_Signal},
		{"NeBACR_b_eBstBrkFdSt1DiagP",     eth1NeBACR_b_eBstBrkFdSt1DiagP_Signal},
	};

	signalSetphysList.clear();
	signalLenphysList.clear();
	signalList_float_Phys.clear();
	sendSignalsList_Phys.clear();
	eth1HwSignalMap.clear();
	eth1OldPhysValueMap.clear();

	for (const auto& sig : signals_xml)
	{
		signalSetphysList.emplace(sig.label, sig.set_phys);
		signalLenphysList.emplace(sig.label, sig.length_phys);

		auto physIdVal = std::make_shared<IdValuePair<double>>();
		std::string physCpName = sig.label + "__Sig";
		physIdVal->Id = sig.set_phys;
		physIdVal->Name = sig.label;
		physIdVal->Length = sig.length_phys;
		physIdVal->OldValue = sig.defValPhys > 0;
		signalList_float_Phys.emplace(physCpName, physIdVal);
		sendSignalsList_Phys.emplace(physCpName, sig);

		if (auto it = m.find(sig.label); it != m.end())
		{
			it->second.get().setAddress(sig.set_phys);
			eth1HwSignalMap.emplace(physCpName, it->second);
		}
		else
		{
			LOG(WARNING) << "SignalListData: no HwComDataObject found for XML label=" << sig.label;
		}
	}

	LOG(INFO) << "SignalListData: eth1HwSignalMap size=" << eth1HwSignalMap.size();
	LOG(INFO) << "SignalListData: signalList_float_Phys size=" << signalList_float_Phys.size();
}

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1Core::FRAMEListData()
{
	auto frames_xml = helper->Get_readxml()->GetSetFrameList(nodeName.c_str());

	FrameManipList.clear();
	FrameList.clear();
	sendFrameList.clear();

	for (const auto& sig : frames_xml)
	{
		FrameManipList.emplace(sig.label, sig.setTx);

		auto idval = std::make_shared<IdValuePair<double>>();
		std::string cpName = sig.label + "__Frame";
		idval->Id = sig.setTx;
		idval->Name = sig.label;
		idval->Length = sig.Setlength;
		FrameList.emplace(cpName, idval);
		sendFrameList.emplace(cpName, sig);

		if (sig.label == WakeUp_VLAN_111_Frame_Tx)
		{
			ETH1_Frame_WuP.setAddress(sig.setTx);
			CommonVars->CCU_ETH1_WuP_Frm_Set_Address->quantity = none_t(ETH1_Frame_WuP.getAddress());
		}
		else if (sig.label == HeartBeat_VLAN_111_Frame_Tx)
		{
			ETH1_Frame_Heartbeat.setAddress(sig.setTx);
			CommonVars->CCU_ETH1_HB_Frm_Set_Address->quantity = none_t(ETH1_Frame_Heartbeat.getAddress());
		}
		else if (sig.label == Info_Frame_Tx)
		{
			ETH1_Frame_Info.setAddress(sig.setTx);
			CommonVars->CCU_ETH1_Info_Frm_Set_Address->quantity = none_t(ETH1_Frame_Info.getAddress());
		}
	}

	if (FrameList.empty())
	{
		LOG(INFO) << "ETH1 FrameList is empty.";
		return;
	}
}

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1Core::PDUListData()
{
	auto pdus_xml = helper->Get_readxml()->GetSetPDUList(nodeName.c_str());

	PDUManipList.clear();
	PDULengthList.clear();
	PDUSetList.clear();
	PDUGetList.clear();
	sendPDUList.clear();
	receivePDUList.clear();

	for (const auto& sig : pdus_xml)
	{
		const unsigned int pduLengthBytes = sig.length / 8;

		PDUManipList.emplace(sig.label, sig.set);
		PDULengthList.emplace(sig.label, pduLengthBytes);

		auto setIdVal = std::make_shared<IdValuePair<double>>();
		std::string cpName = sig.label + "__PDU";
		setIdVal->Id = sig.set;
		setIdVal->Name = sig.label;
		setIdVal->Length = pduLengthBytes;
		PDUSetList.emplace(cpName, setIdVal);
		sendPDUList.emplace(cpName, sig);

		auto getIdVal = std::make_shared<IdValuePair<double>>();
		getIdVal->Id = sig.get;
		getIdVal->Name = sig.label;
		getIdVal->Length = pduLengthBytes;
		PDUGetList.emplace(cpName, getIdVal);
		receivePDUList.emplace(cpName, sig);

		if (sig.label == WakeUp_VLAN_111_PDU)
		{
			ETH1_PDU_WuP.setAddress(sig.set);
			ETH1_Custom_Timing_WuP.setAddress(sig.CustomTiming);

			CommonVars->CCU_ETH1_WuP_PDU_Set_Address->quantity = none_t(ETH1_PDU_WuP.getAddress());
			CommonVars->CCU_ETH1_WuP_PDU_Length->quantity = none_t(ETH1_PDU_WuP.getLength());
			CommonVars->CCU_ETH1_WuP_PDU_Custom_Timing->quantity = none_t(ETH1_Custom_Timing_WuP.getAddress());
		}
		else if (sig.label == HeartBeat_VLAN_111_PDU)
		{
			ETH1_PDU_Heartbeat.setAddress(sig.set);
			CommonVars->CCU_ETH1_HB_PDU_Set_Address->quantity = none_t(ETH1_PDU_Heartbeat.getAddress());
			CommonVars->CCU_ETH1_HB_PDU_Length->quantity = none_t(ETH1_PDU_Heartbeat.getLength());
		}
		else if (sig.label == Info_PDU)
		{
			ETH1_PDU_Info.setAddress(sig.set);
			CommonVars->CCU_ETH1_Info_PDU_Set_Address->quantity = none_t(ETH1_PDU_Info.getAddress());
			CommonVars->CCU_ETH1_Info_PDU_Length->quantity = none_t(ETH1_PDU_Info.getLength());
		}
	}

	if (PDUSetList.empty())
	{
		LOG(INFO) << "ETH1 PDUSetList is empty.";
		return;
	}
}

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1Core::GlobalVars_list()
{
	gVarLengthList.clear();
	gVarSetList.clear(); 
	gVarGetList.clear(); 
	gVarList_Phys.clear();

	const auto& v = Plugins::FlexCard3::ETH_Manipulation::ETH_Manipulation::getInstance()->Get_readxml()->getGlobalVarList();
	std::unordered_map<std::string, std::reference_wrapper<decltype(gVarIgnitionState)>> m{
		{"gVarIgnitionState",gVarIgnitionState},{"gVarSetWuP",gVarSetWuP},{"gVarAlternativeTiming",gVarAlternativeTiming},
		{"gVarAlternativeTimingEth1",gVarAlternativeTimingEth1},{"gVarAlternativeTimingEth2",gVarAlternativeTimingEth2},
		{"gVarFcCounterValueSetAll",gVarFcCounterValueSetAll},{"gVarSaveFreshnessAll",gVarSaveFreshnessAll},
		{"gVarService3163Rcvd",gVarService3163Rcvd},{"gVarService3164Rcvd",gVarService3164Rcvd},{"gVarSetFreshnessAll",gVarSetFreshnessAll}
	};
	auto mk = [](const auto& s) { auto p = std::make_shared<IdValuePair<double>>(); p->Id = s.set; p->Name = s.label; p->Length = s.length; return p; };

	for (const auto& s : v) {
		gVarSetList[s.label] = s.set; gVarLengthList[s.label] = s.length; gVarGetList[s.label] = s.get;
		if (auto it = m.find(s.label); it != m.end()) it->second.get().setAddress(s.set);
		gVarList_Phys[s.label] = mk(s);
	}
}