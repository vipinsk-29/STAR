/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.MG_GM_BEV3_205_9p9_V01_M_P100
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

#include "../MG_GM_BEV3_205_9p9_V01_M.h"
#include "ModelCore/Quantity/Literals.h"

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::MG_GM_BEV3_205_9p9_V01_M::P100(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;

	const auto rbs_name = RBSName->quantity.get_value();
}
