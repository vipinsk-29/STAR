/******************************************************************/
/* FILE: Kernel.FL3X.RBSGeneral_HiL_P380
/* SW-COMPONENT: C++-genericToolChainModelComponent
/* DESCRIPTION: Source is used to build a Labcar model component for a generic ToolChain, based on C++ code
/* COPYRIGHT: (C) 2026 Robert Bosch GmbH
/*
/* The reproduction, distribution and utilization of this file as
/* well as the communication of its contents to others without express
/* authorization is prohibited. Offenders will be held liable for the
/* payment of damages. All rights reserved in the event of the grant
/* of a patent, utility model or design.
/******************************************************************/

#include "../RBSGeneral_HiL.h"
#include <g3log/g3log.hpp>
#include <g3log/loglevels.hpp>
#include <PC_HW_Int_Light/Header.h>

void Kernel::FL3X::RBSGeneral_HiL::P380(::model_core::common::time::SimulationTime* time_info)
{
	using namespace model_core::quantity::literals;

	_taskMeasurement380.start_measurement("Kernel::FL3X::RBSGeneral_HiL::P380");
	tim->quantity = tim->quantity + time_info->dt;

	// --- Per-call instrumentation ---
	static std::uint64_t p380_cycle_count = 0;      // total P380 invocations
	static std::uint64_t send_buffer_calls = 0;     // total send_buffer invocations
	static std::uint64_t send_buffer_success = 0;   // cumulative success
	static std::uint64_t send_buffer_fail = 0;      // cumulative fail

	++p380_cycle_count;

	readSlot_Index = setValueHWBuffer(true, read_Index);

	if (readSlot_Index > 0)
	{
		++send_buffer_calls;
		success = pc_hw_interface_light->send_buffer(this->cardNumber, s_hwBuffer, readSlot_Index, send_wait_control->quantity.get_value());

		if (success)
		{
			++send_buffer_success;
		}
		else
		{
			++send_buffer_fail;
			LOG(WARNING) << "[RBS General: P380] send_buffer FAILED - call#=" << send_buffer_calls;
		}

		// Log for EACH call
		LOG(INFO) << "[RBS General: P380] send_buffer call#=" << send_buffer_calls
			<< "	RBS General p380_cycle#=" << p380_cycle_count
			<< "	readSlot_Index=" << readSlot_Index
			<< "	wait=" << (send_wait_control->quantity.get_value())
			<< "	success=" << (success ? "true" : "false")
			<< "	totals{ok=" << send_buffer_success;
	}

	_taskMeasurement380.stop_measurement();
}