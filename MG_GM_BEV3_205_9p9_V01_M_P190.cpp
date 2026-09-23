/******************************************************************/
/* FILE: EID.Net.ETH.GM_BEV3_205_9p9_V01_M.MG_GM_BEV3_205_9p9_V01_M_P190
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
#include <fstream>
#include <iostream>
#include <string>

#include "../MG_GM_BEV3_205_9p9_V01_M.h"
#include "ModelCore/Quantity/Literals.h"

#include <g3log/g3log.hpp>
#include "Global/macros.h"
#include "pugixml.hpp"
#include "XmlSignalReader/XmlSignalReader.h"
#include "ErrHandlingPin/ErrHandlingPin.h"


#if defined(_WIN32) || defined(_WIN64) //SiL
#include <direct.h> //windows only
#define getcwd(p1)  _getcwd(p1, sizeof(p1))
#else
#include <unistd.h>
#define getcwd(p1)  getcwd(p1, sizeof(p1))
#endif

void EID::Net::ETH::GM_BEV3_205_9p9_V01_M::MG_GM_BEV3_205_9p9_V01_M::P190(::model_core::common::time::SimulationTime* time_info)
{
	// ToDo: implement process
	using namespace model_core::quantity::literals;
    Kernel::ErrHandling::ErrHandlingPin::ErrHandlingPin* errorHandle = Kernel::ErrHandling::ErrHandlingPin::ErrHandlingPin::getInstance();

	if (PC_HW_Int_Client == nullptr) {
		// Log a fatal error or throw an exception
		std::cerr << "FATAL: PC_HW_Int_Client is not initialized." << std::endl;
		// Depending on the system's design, you might want to abort or throw.
		abort();
	}
	pc_hw_int = PC_HW_Int_Client->getPcHwIntLibVersion();

	if (PC_HW_Int_Lt_Client == nullptr) {
		// Log a fatal error or throw an exception
		std::cerr << "FATAL: PC_HW_Int_Lt_Client is not initialized." << std::endl;
		abort();
	}
	pc_hw_interface_light = PC_HW_Int_Lt_Client->getPcHwIntLightVersion();

	if (PC_HW_Int_Client == nullptr) {
		// Log a fatal error or throw an exception
		std::cerr << "FATAL: PC_HW_Int_Client is not initialized." << std::endl;
		abort();
	}
	pc_hw_int = PC_HW_Int_Client->getPcHwIntLibVersion();

	char tempfolder[255];
	getcwd(tempfolder); //using macros defintion getcwd(tempfolder, sizeof(tempfolder));
	std::string project_unpacked_current_path(tempfolder);

	//Check XML file availablity
#if defined(_WIN32) || defined(_WIN64) 
	std::string xml_rooted_filename = project_unpacked_current_path + "/ProtocolConfig/" + static_cast<std::string>(RBSName->quantity.get_value()) + ".xml";
	const char* ethernet_XML_File_Path = xml_rooted_filename.c_str();
	fprintf(stdout, "EthernetParser_start_up: Loading ethernet_XML_File_Path file from path %s\n", ethernet_XML_File_Path);
	LOG(INFO) << "EthernetParser_start_up: Loading ethernet_XML_File_Path file from path: " << ethernet_XML_File_Path;
#else
	std::string xml_rooted_filename = "./ProtocolConfig/" + static_cast<std::string>(RBSName->quantity.get_value()) + ".xml";
	const char* ethernet_XML_File_Path = xml_rooted_filename.c_str();
	fprintf(stdout, "EthernetParser_start_up: Loading ethernet_XML_File_Path file from path %s\n", ethernet_XML_File_Path);
	LOG(INFO) << "EthernetParser_start_up: ethernet_XML_File_Path: Loading file from path: " << ethernet_XML_File_Path;
#endif
	std::ifstream myfile_xml(ethernet_XML_File_Path);
	if (!myfile_xml.is_open())
	{
		std::cout << "ERROR: EthernetParser_start_up:  Cannot find file! Missing/ReadError of File: " << ethernet_XML_File_Path << std::endl;
		LOG(FATAL) << "ERROR: EthernetParser_start_up:  Cannot find file! Missing/ReadError of File: " << ethernet_XML_File_Path << std::endl;
		return;
	}
	myfile_xml.close();

	// Check s19 file availability
#if defined(_WIN32) || defined(_WIN64)
	std::string s19_filename = project_unpacked_current_path + "/" + static_cast<std::string>(RBSName->quantity.get_value()) + "/FC_RBS_FlexCard-PCIe3.s19";
	const char* s19_File_Path = s19_filename.c_str();
	LOG(INFO) << "commEthernet_start_up: Loading s19_File_Path file from path: " << s19_File_Path;
#else
	std::string s19_filename = "./" + static_cast<std::string>(RBSName->quantity.get_value()) + "/FC_RBS_FlexCard-PCIe3.s19";
	const char* s19_File_Path = s19_filename.c_str();
	LOG(INFO) << "commEthernet_start_up: s19_File_Path: Loading file from path: " << s19_File_Path;
#endif
	std::ifstream myfile_s19(s19_File_Path);
	if (!myfile_s19.is_open())
	{
		std::cout << "ERROR: commEthernet_start_up:  Cannot find file! Missing/ReadError of File: " << s19_File_Path << std::endl;
		LOG(FATAL) << "ERROR: commEthernet_start_up:  Cannot find file! Missing/ReadError of File: " << s19_File_Path << std::endl;
		return;
	}
	myfile_s19.close();

	//======================== XML Reading ========================================================s
	auto ethManip = Plugins::FlexCard3::ETH_Manipulation::ETH_Manipulation::getInstance();
	auto xmlReader = ethManip->Get_readxml();

	static bool initialized = false;
	if (!initialized) {
		xmlReader->set_XML_FilePath(ethernet_XML_File_Path);
		int xmlLoadResult = xmlReader->load_and_parse_XML();

		if (xmlLoadResult != 0) {
			std::cerr << "ERROR: Failed to load and parse Ethernet XML, code: " << xmlLoadResult << std::endl;
			return;
		}
		initialized = true;
	}
		InitializeAllLists();

	//======================== XML Reading ========================================================

	//To read BusInfo [ETH1, ETH2, CAN1...]
	for (size_t i = 0; i < xmlReader->Businfo().size(); i++)
	{
		BusInfo->quantity.set_value_at(i, xmlReader->Businfo()[i]);
	}

	//To read .s19 BinNetTicksUTC e.g.,Build Time : Fri, 21 Aug 2026 11 : 10 : 01 GMT(639229074015795829)
	auto binFileTicks = helper->Get_readxml()->GetBinNetTicksUTC();
	auto sha256Xml = helper->Get_readxml()->GetSha256();
	LOG(INFO) << "MG_P190: BinNetTicksUTC=" << binFileTicks;
	LOG(INFO) << "MG_P190: sha256Xml=" << sha256Xml;

	std::string shaResult = CCHIL::Star::FC3_FileUtilities::calculate_file_sha256(s19_filename);

	LOG(INFO) << "MG_P190: shaResult=" << shaResult;
	//compare sha256 values
	if (shaResult.compare(sha256Xml) == 0)
	{
		LOG(INFO) << "Check timestamp";
		//Read Time Stamp from RBS
		uint64_t rbsTimeStamp = pc_hw_int->getFlexCardTimeStampReq(cardNumber);
		
		if (!CCHIL::Star::FC3_FileUtilities::CheckTimeStamps(rbsTimeStamp, binFileTicks))
		{
			//wait x milli seconds for download
			uint32_t tout_ms = 40 * 1000;
			LOG(INFO) << "Call Flash process - wait for: " << tout_ms;
			//Flash procss with timeout and check
			bool flashStatus = pc_hw_int->flexCardRbsDownload(this->cardNumber, s19_filename, tout_ms);
			//Error message to Model error window
			if (!flashStatus)
			{
				errorHandle->enterMessage(Plugins::Global::ErrorType::ErrorType_Error, this->get_module_path(), "P190", "RBS flashing of FlexCard3 failed.");
				LOG(FATAL) << "RBS flashing of FlexCard3 failed";
			}
		
		}
	}
	else
	{
		//SHA256 is not fitting
		errorHandle->enterMessage(Plugins::Global::ErrorType::ErrorType_Error, this->get_module_path(), "P190", "File check failed - Please check the s19 RBS File and the beloning XML.");
		LOG(FATAL) << "Please check the s19 RBS File and the beloning XML";
	}

}