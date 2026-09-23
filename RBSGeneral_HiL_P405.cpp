/******************************************************************/
/* FILE: Kernel.FL3X.RBSGeneral_HiL_P405
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
#include "ModelCore/Quantity/Literals.h"

void Kernel::FL3X::RBSGeneral_HiL::P405(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;

	LOG(INFO) << "Kernel::FL3X::RBSGeneral_HiL::P405: entered...";
	/*if (_socketCan_hil != nullptr)
	{
		LOG(INFO) << "=============FL3X Card set interface down======";
		_socketCan_hil->deleteIpLinkConfig();
		LOG(INFO) << "=============Start FL3X Card closure===========";
		int32_t retVal = _socketCan_hil->closeSockets();
		LOG(INFO) << "=============End FL3X Card closure=============";
	}
	else
	{
		LOG(INFO) << "Can not close socket in FL3X::RBSGeneral_HiL";
	}*/

	_taskMeasurement.close_measurement();
	_taskMeasurement380.close_measurement();
	_taskMeasurement.print_measuremnt();
	_taskMeasurement380.print_measuremnt();
	LOG(INFO) << "Kernel::FL3X::RBSGeneral_HiL::P405: finished.";
}