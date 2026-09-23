/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.ETH1_P380
/* SW-COMPONENT: C++-genericToolChainModelComponent
/* DESCRIPTION: Source is used to build a Labcar model component for a generic ToolChain, based on C++ code
/* COPYRIGHT: (C) 2025 Robert Bosch GmbH
/******************************************************************/

#include "../ETH1.h"
#include "ModelCore/Quantity/Literals.h"
#include <iomanip>

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1::P380(::model_core::common::time::SimulationTime* time_info)
{
	using namespace model_core::quantity::literals;

	wait = CommonVars->send_wait_ctrl->quantity.get_value();

	if (eth1HwSignalMap.empty())
	{
		LOG(WARNING) << "P380: eth1HwSignalMap is empty. Did SignalListData() run?";
		return;
	}

	bool anySignalChanged = false;
	std::uint32_t changedSignals = 0U;
	HwSerializer::SomeIpBigEndianPolicy policy;

	for (auto const& floatSig_Phys : signalList_float_Phys)
	{
		const std::string& physCpName = floatSig_Phys.first;
		const auto& signalMeta = floatSig_Phys.second;

		if (signalMeta == nullptr)
		{
			LOG(WARNING) << "P380: signalMeta is null for key=" << physCpName;
			continue;
		}

		auto moduloIt = moduloSignalList.find(physCpName);
		if (moduloIt == moduloSignalList.end())
		{
			LOG(WARNING) << "P380: moduloSignalList entry not found for key=" << physCpName;
			continue;
		}

		auto hwIt = eth1HwSignalMap.find(physCpName);
		if (hwIt == eth1HwSignalMap.end())
		{
			//LOG(WARNING) << "P380: eth1HwSignalMap entry not found for key=" << physCpName;
			continue;
		}

		auto xilAccessor = moduloIt->second->get_xil_value_access_object();
		if (xilAccessor == nullptr)
		{
			LOG(WARNING) << "P380: XIL accessor is null for key=" << physCpName;
			continue;
		}

		const double currentValue = xilAccessor->get_float();

		auto oldIt = eth1OldPhysValueMap.find(physCpName);
		const bool firstTime = (oldIt == eth1OldPhysValueMap.end());
		const double oldValue = firstTime ? 0.0 : oldIt->second;

		if (/*firstTime ||*/ oldValue != currentValue)
		{
			auto& hwSignal = hwIt->second.get();

			LOG(INFO) << "========================================";
			LOG(INFO) << "ETH1 P380: Processing Signal: " << physCpName;
			LOG(INFO) << "ETH1 P380: Physical Value (double): " << std::fixed << std::setprecision(2) << currentValue;
			LOG(INFO) << "========================================";

			hwSignal.setPhysicalRaw(currentValue);

			LOG(INFO) << "ETH1 P380: About to call toRaw() for signal: " << physCpName;
			LOG(INFO) << "ETH1 P380: Serializing to big-endian format";

			hwSignal.toRaw(policy);

			LOG(INFO) << "ETH1 P380: Signal [" << physCpName << "] serialized successfully";
			LOG(INFO) << "========================================";

			//readSlot_Index = setValueHWBuffer(false, hwSignal);
			setValueHWBuffer(false, hwSignal);

			eth1OldPhysValueMap[physCpName] = currentValue;
			anySignalChanged = true;
			++changedSignals;

			//LOG(INFO) << "ETH1 P380: Signal serialized and added to buffer. Slot index: " << readSlot_Index;
		}
	}

	/*if (anySignalChanged && readSlot_Index > 0)
	{
		LOG(INFO) << "ETH1 P380: Sending buffer with " << changedSignals << " changed signals";

		success = pc_hw_interface_light->send_buffer(this->cardNumber, s_hwBuffer, readSlot_Index, wait);

		readSlot_Index = setValueHWBuffer(true, read_Index);
	}*/
}