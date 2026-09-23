/******************************************************************/
/* FILE: CCHIL.Star.FC3_CardHandling_P405
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

#include "../FC3_CardHandling.h"
#include "ModelCore/Quantity/Literals.h"

void CCHIL::Star::FC3_CardHandling::P405(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;

	LOG(INFO) << "STOP_FLEXCARD Standard Interface";
	_pc_hw_interface->closeFlexCard(this->cardNumber);

	if (_pc_hw_interface != nullptr)
	{
		_pc_hw_interface.reset();
		_pc_hw_interface = nullptr; // ToDo: check if we are fine with this at the time to destroy?
	}

	LOG(INFO) << "STOP_FLEXCARD Light Interface";
	bool lightInterfaceClosed = _pc_hw_interface_light->closeFlexCard_HW_Light(this->cardNumber);
	LOG(INFO) << "lightInterfaceStatus " << lightInterfaceClosed;

	if (_pc_hw_interface_light != nullptr)
	{
		_pc_hw_interface_light.reset();
		_pc_hw_interface_light = nullptr; // ToDo: check if we are fine with this at the time to destroy?
	}

	_taskMeasurement.close_measurement();
	_taskMeasurement.print_measuremnt();
	LOG(INFO) << "CCHIL::Star::FC_CardHandling::P405: finished...";
}