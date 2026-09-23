
/******************************************************************/
/* FILE: Kernel.FL3X.RBSGeneral_HiL_P205
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
#include <g3log/g3log.hpp>
#include <g3log/loglevels.hpp>
#include "Global/macros.h"

void Kernel::FL3X::RBSGeneral_HiL::P205(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;
	
	_taskMeasurement.start_measurement("Kernel::FL3X::RBSGeneral_HiL::P205");

	P205readSlot_Index = readValueHWBuffer(true, read_Index);

	if (P205readSlot_Index > 0)
	{
		success = pc_hw_interface_light->read_buffer(this->cardNumber, r_hwBuffer, P205readSlot_Index);
		LOG(INFO) << "[RBS General HiL: P205] Entered : readSlot_Index=" << P205readSlot_Index;
	}
	
	_taskMeasurement.stop_measurement();
}