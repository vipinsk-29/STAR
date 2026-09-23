/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.ETH1_P195
/* SW-COMPONENT: C++-genericToolChainModelComponent
/* DESCRIPTION: Source is used to build a Labcar model component for a generic ToolChain, based on C++ code
/* COPYRIGHT: (C) 2025 Robert Bosch GmbH
/******************************************************************/

#include "../ETH1.h"
#include "ModelCore/Quantity/Literals.h"
using namespace Plugins::FlexCard3::PC_HW_Interface::Light;

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1::P195(::model_core::common::time::SimulationTime* time_info)
{
	using namespace model_core::quantity::literals;

	InitializeAllLists();
	Init = false;

	cycleTimer = globalPlugin.dt.get_value_in_unit<::model_core::quantity::time::Second>();
	cycleTimeWuPTickCount = (double)(ETH1_WuP_CycleTimeTickCount->quantity.get_value() / ETH1_CycleTimeDividend->quantity.get_value());
	cycleTimeWuPInitTickCount = (double)(ETH1_WuP_CycleTimeInitTickCount->quantity.get_value() / ETH1_CycleTimeDividend->quantity.get_value());
	cycleTimeHBTickCount = (double)(ETH1_HB_CycleTimeTickCount->quantity.get_value() / ETH1_CycleTimeDividend->quantity.get_value());
	cycleTimeInfoTickCount = (double)(ETH1_Info_CycleTimeTickCount->quantity.get_value() / ETH1_CycleTimeDividend->quantity.get_value());
	cycleTimeSomeIPTickCount = (double)(ETH1_SomeIP_CycleTimeTickCount->quantity.get_value() / ETH1_CycleTimeDividend->quantity.get_value());

	for (const auto& floatSignal_Phys : signalList_float_Phys)
	{
		auto moduloIt = moduloSignalList.find(floatSignal_Phys.first);
		if (moduloIt == moduloSignalList.end())
		{
			LOG(WARNING) << "P195: moduloSignalList entry not found for key=" << floatSignal_Phys.first;
			continue;
		}

		auto signalSetIt = signalSetphysList.find(floatSignal_Phys.second->Name);
		if (signalSetIt == signalSetphysList.end())
		{
			LOG(WARNING) << "P195: signalSetphysList entry not found for name=" << floatSignal_Phys.second->Name;
			continue;
		}

		auto helperObj = std::make_unique<Defs::ManipulationSignalHelperfloat>(
			floatSignal_Phys.first,
			moduloIt->second);

		helperObj->tal_id = signalSetIt->second;

		FloatSigManipulationHelperList.push_back(std::move(helperObj));
	}

/*	ETH1_PDU_WuP.setRaw(setRawPduWakeUpBuffer_V22.data(), CommonVars->CCU_ETH1_WuP_PDU_Length->quantity.get_value());
	setValueHWBuffer(false,ETH1_PDU_WuP);
	setValueHWBuffer(false, ETH1_Frame_WuP);

	ETH1_PDU_Heartbeat.setRaw(setRawPduHBBuffer_V22.data(), CommonVars->CCU_ETH1_HB_PDU_Length->quantity.get_value());
	setValueHWBuffer(false, ETH1_PDU_Heartbeat);
	setValueHWBuffer(false, ETH1_Frame_Heartbeat);

	ETH1_PDU_Info.setRaw(setRawPduInfoBuffer_V22.data(), 28); // CommonVars->CCU_ETH1_Info_PDU_Length->quantity.get_value());
	setValueHWBuffer(false, ETH1_PDU_Info);
	setValueHWBuffer(false, ETH1_Frame_Info);*/
	/*
	//Default values
	YeBACR_a_eBstVeh_AxP__Sig->quantity = (none_t)-2.99977;
	eth1YeBACR_a_eBstVeh_AxP_Signal.setPhysicalRaw(YeBACR_a_eBstVeh_AxP__Sig->quantity.get_value());
	setValueHWBuffer(false, eth1HwSignalMap.at("YeBACR_a_eBstVeh_AxP__Sig"));

	VeBACR_a_eBstVehAyP__Sig->quantity = (none_t)0.05025;
	eth1VeBACR_a_eBstVehAyP_Signal.setPhysicalRaw(VeBACR_a_eBstVehAyP__Sig->quantity.get_value());
	setValueHWBuffer(false, eth1HwSignalMap.at("VeBACR_a_eBstVehAyP__Sig"));*/
}