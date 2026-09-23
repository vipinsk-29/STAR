
/******************************************************************/
/* FILE: Kernel.FL3X.RBSGeneral_HiL_P110
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
#include "ErrHandlingPin/ErrHandlingPin.h"
#include "Global/macros.h"

void Kernel::FL3X::RBSGeneral_HiL::P110(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;
	_testbench_manager->_isAvailable_FL3XCard = false;
	
	// Initialize TaskMeasurement_HIL
	_taskMeasurement.init_measurement();
	_taskMeasurement380.init_measurement();
	LOG(INFO) << "RBSGeneral_HiL::P110: Entered.";
	
	pc_hw_interface_light = PC_HW_Int_Lt_Client->getPcHwIntLightVersion();
	LOG(INFO) << "RBSGeneral_HiL::P110: pc_hw_interface_light Version " << pc_hw_interface_light;
}