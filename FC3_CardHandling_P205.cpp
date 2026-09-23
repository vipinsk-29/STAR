/******************************************************************/
/* FILE: CCHIL.Star.FC3_CardHandling_P205
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
#include "Global/macros.h"

void CCHIL::Star::FC3_CardHandling::P205(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;
	_taskMeasurement.start_measurement("CCHIL::Star::FC_CardHandling::P205");
	timeSinceLastSending += globalPlugin.dt;
	double schedulerTime = 5.0;
	double testSendschedulerTime = 0.1;
	static uint8_t cnt = 0;

	//check to start or stop the application
	if (timeSinceLastSending.get_value() >= schedulerTime)
	{
		//start FlexCard Application
		if (true == CP_Start_FC3_Application->quantity.get_value())
		{
			auto start = std::chrono::high_resolution_clock::now();
			_pc_hw_interface->flexCardAppStartReq(this->cardNumber);
			auto stop = std::chrono::high_resolution_clock::now();
			CP_Start_FC3_Application->quantity = bool_t(false);
			auto ellapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
			LOG(INFO) << "time flexCardAppStartReq: " << ellapsed.count() << " micro seconds";
		}

		//stop FlexCard Application
		if (true == CP_Stop_FC3_Application->quantity.get_value())
		{
			auto start = std::chrono::high_resolution_clock::now();
			_pc_hw_interface->flexCardAppStopReq(this->cardNumber);
			auto stop = std::chrono::high_resolution_clock::now();
			CP_Stop_FC3_Application->quantity = bool_t(false);
			auto ellapsed = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
			LOG(INFO) << "time flexCardAppStopReq: " << ellapsed.count() << " micro seconds";
		}
		timeSinceLastSending = 0_s;
	}

	_taskMeasurement.stop_measurement();
}

