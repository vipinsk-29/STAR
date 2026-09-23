/******************************************************************/
/* FILE: CCHIL.Star.FC3_CardHandling_P102
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


void CCHIL::Star::FC3_CardHandling::P102(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;

	// Initialize TaskMeasurement_HIL
	_taskMeasurement.init_measurement();

	LOG(INFO) << "========START_FLEXCARD_INIT STANDARD INTERFACE========";
	//get the common pointer to the used Lib
	_pc_hw_interface = PC_HW_Int_Client->getPcHwIntLibVersion();
	LOG(INFO) << "_pc_hw_interface = " << _pc_hw_interface;
	_pc_hw_interface_light = PC_HW_Int_Lt_Client->getPcHwIntLightVersion();
	LOG(INFO) << "_pc_hw_interface_light = " << _pc_hw_interface_light;
	std::string STAR_PREFIX = _pc_hw_interface->STAR_PREFIX;
	LOG(INFO) << STAR_PREFIX << "Using PC Hardware Library Version " << _pc_hw_interface->name;

	//open the FlexCard interface and
	if (_pc_hw_interface->openFlexCard(this->cardNumber))
	{
		_pc_hw_interface->getFlexDeviceName(this->cardNumber);
		_pc_hw_interface->getFlexCardStatus(this->cardNumber);
		_pc_hw_interface->getFlexCardHwConfigReq(this->cardNumber);
		_pc_hw_interface->getFlexCardVersionReq(this->cardNumber);
		_pc_hw_interface->getFlexCardVersionStringReq(this->cardNumber);
		_pc_hw_interface->getFlexCardLicenseConfigReq(this->cardNumber);
		_pc_hw_interface->getFlexCardSwConfigReq(this->cardNumber);
		_pc_hw_interface->getFlexCardFPGAConfigReq(this->cardNumber);
		_pc_hw_interface->getFlexCardFPGAImagesReq(this->cardNumber);
		_pc_hw_interface->getFlexCardRBSStatusReq(this->cardNumber);
		_pc_hw_interface->getFlexCardTimeStampReq(this->cardNumber);
		_pc_hw_interface->getFlexCardStatusReq(this->cardNumber);
		_pc_hw_interface->getFlexCardRBSChannelsInfoReq(this->cardNumber);
		_pc_hw_interface->getFlexCardDllVersion(this->cardNumber);
	}
	else
	{
		LOG(WARNING) << "FlexCard3 not configured";
	}
	LOG(INFO) << "========START_FLEXCARD_INIT LIGHT INTERFACE========";
	bool lightInterfaceOpened = _pc_hw_interface_light->openFlexCard_HW_Light(this->cardNumber);
	LOG(INFO) << "lightInterfaceStatus " << lightInterfaceOpened;

	//MAJOR & MINOR version of the library should be checked to ensure compatibility, PATCH and BUILD can be used for information purpose
	hw_com_light_version_get(&libVersion);

	//GUI Implementation is pending
	Build->quantity = (unsigned_none_t) static_cast<int>(libVersion.Build);
	Major->quantity = (unsigned_none_t) static_cast<int>(libVersion.Major);
	Minor->quantity = (unsigned_none_t) static_cast<int>(libVersion.Minor);
	Patch->quantity = (unsigned_none_t) static_cast<int>(libVersion.Patch);

	LOG(INFO) << "Build: " << static_cast<int>(libVersion.Build) <<
		"; Major: " << static_cast<int>(libVersion.Major) <<
		"; Minor: " << static_cast<int>(libVersion.Minor) <<
		"; Patch: " << static_cast<int>(libVersion.Patch) << std::endl;

}