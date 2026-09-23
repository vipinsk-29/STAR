/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.ETH2_P195
/* SW-COMPONENT: C++-genericToolChainModelComponent
/* DESCRIPTION: Source is used to build a Labcar model component for a generic ToolChain, based on C++ code
/* COPYRIGHT: (C) 2025 Robert Bosch GmbH
/******************************************************************/

#include "../ETH2.h"
#include "ModelCore/Quantity/Literals.h"
using namespace Plugins::FlexCard3::PC_HW_Interface::Light;

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH2::P195(::model_core::common::time::SimulationTime* time_info)
{
	using namespace model_core::quantity::literals;

	InitializeAllLists();

	cycleTimer = globalPlugin.dt.get_value_in_unit<::model_core::quantity::time::Second>();
	cycleTimeWuPTickCount = (double)(ETH2_WuP_CycleTimeTickCount->quantity.get_value() / ETH2_CycleTimeDividend->quantity.get_value());
	cycleTimeWuPInitTickCount = (double)(ETH2_WuP_CycleTimeInitTickCount->quantity.get_value() / ETH2_CycleTimeDividend->quantity.get_value());
	cycleTimeHBTickCount = (double)(ETH2_HB_CycleTimeTickCount->quantity.get_value() / ETH2_CycleTimeDividend->quantity.get_value());
	cycleTimeInfoTickCount = (double)(ETH2_Info_CycleTimeTickCount->quantity.get_value() / ETH2_CycleTimeDividend->quantity.get_value());
	cycleTimeSomeIPTickCount = (double)(ETH2_SomeIP_CycleTimeTickCount->quantity.get_value() / ETH2_CycleTimeDividend->quantity.get_value());

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

/*	ETH2_PDU_WuP.setRaw(setRawPduWakeUpBuffer_V23.data(), CommonVars->CCU_ETH2_WuP_PDU_Length->quantity.get_value());
	setValueHWBuffer(false, ETH2_PDU_WuP);
	setValueHWBuffer(false, ETH2_Frame_WuP);

	ETH2_PDU_Heartbeat.setRaw(setRawPduHBBuffer_V23.data(), CommonVars->CCU_ETH2_HB_PDU_Length->quantity.get_value());
	setValueHWBuffer(false, ETH2_PDU_Heartbeat);
	setValueHWBuffer(false, ETH2_Frame_Heartbeat);

	ETH2_PDU_Info.setRaw(setRawPduInfoBuffer_V23.data(), 28); // CommonVars->CCU_ETH2_Info_PDU_Length->quantity.get_value());
	setValueHWBuffer(false, ETH2_PDU_Info);
	setValueHWBuffer(false, ETH2_Frame_Info);*/
	/*
	//Default values
	YeBACR_a_eBstVeh_AxS__Sig->quantity = (none_t)-2.99977;
	eth2YeBACR_a_eBstVeh_AxS_Signal.setPhysicalRaw(YeBACR_a_eBstVeh_AxS__Sig->quantity.get_value());
	setValueHWBuffer(false, eth2YeBACR_a_eBstVeh_AxS_Signal);

	VeBACR_a_eBstVehAyS__Sig->quantity = (none_t)0.05025;
	eth2VeBACR_a_eBstVehAyS_Signal.setPhysicalRaw(VeBACR_a_eBstVehAyS__Sig->quantity.get_value());
	setValueHWBuffer(false, eth2YeBACR_a_eBstVeh_AxS_Signal);*/
}