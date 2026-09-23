
#include "ManipHelperClass.h"
/*
std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationHelper*> EID::Net::ETH::GM_BEV3::Defs::generate_pdumanipulation_list(const std::string& start, const std::string& end, std::map<std::string, model_core::model::Signal*> moduloSignalList)
{
	std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationHelper*> helper_list;
	for (auto element : moduloSignalList)
	{
		if (element.first.find(start) != std::string::npos) {
			if (element.first.find(end + "_Manip") != std::string::npos)
			{
				size_t startPos = element.first.find(start);
				size_t endPos = element.first.find(end + "_Manip");

				if (startPos != std::string::npos && endPos != std::string::npos)
				{
					// Extract substring between 'start' and 'end'
					std::string name = element.first.substr(startPos + start.length(), endPos - startPos - start.length());
					//std::cout << "found!" << '\n';
					//instance ManipulationHelper();
					//push to vector
					Defs::ManipulationHelper* found_manipul_signal = new Defs::ManipulationHelper(name, element.second, moduloSignalList, start, end);
					helper_list.push_back(found_manipul_signal);
				}
			}
		}
	}
	return helper_list;
}

std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationHelperCheckSum*> EID::Net::ETH::GM_BEV3::Defs::generate_checksummanipulation_list(const std::string& start, const std::string& end, std::map<std::string, model_core::model::Signal*> moduloSignalList)
{
	std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationHelperCheckSum*> helper_list;
	for (auto element : moduloSignalList)
	{
		if (element.first.find(start) != std::string::npos) {
			if (element.first.find(end + "_Manip") != std::string::npos)
			{
				size_t startPos = element.first.find(start);
				size_t endPos = element.first.find(end + "_Manip");

				if (startPos != std::string::npos && endPos != std::string::npos)
				{
					// Extract substring between 'start' and 'end'
					std::string name = element.first.substr(startPos + start.length(), endPos - startPos - start.length());
					//std::cout << "found!" << '\n';
					//instance ManipulationHelper();
					//push to vector
					Defs::ManipulationHelperCheckSum* found_manipul_signal = new Defs::ManipulationHelperCheckSum(name, element.second, moduloSignalList, start, end);
					helper_list.push_back(found_manipul_signal);
				}
			}
		}
	}
	return helper_list;
}

std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationHelperCounter*> EID::Net::ETH::GM_BEV3::Defs::generate_countermanipulation_list(const std::string& start, const std::string& end, std::map<std::string, model_core::model::Signal*> moduloSignalList)
{
	std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationHelperCounter*> helper_list;
	for (auto element : moduloSignalList)
	{
		if (element.first.find(start) != std::string::npos) {
			if (element.first.find(end + "_Manip") != std::string::npos)
			{
				size_t startPos = element.first.find(start);
				size_t endPos = element.first.find(end + "_Manip");

				if (startPos != std::string::npos && endPos != std::string::npos)
				{
					// Extract substring between 'start' and 'end'
					std::string name = element.first.substr(startPos + start.length(), endPos - startPos - start.length());
					//std::cout << "found!" << '\n';
					//instance ManipulationHelper();
					//push to vector
					Defs::ManipulationHelperCounter* found_manipul_signal = new Defs::ManipulationHelperCounter(name, element.second, moduloSignalList, start, end);
					helper_list.push_back(found_manipul_signal);
				}
			}
		}
	}
	return helper_list;
}

std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationSignalHelperBoolean*> EID::Net::ETH::GM_BEV3::Defs::generate_boolsigmanipulation_list(const std::string& start, const std::string& end, std::map<std::string, model_core::model::Signal*> moduloSignalList, float offset, float factor)
{
	std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationSignalHelperBoolean*> helper_list;

	for (auto element : moduloSignalList)
	{
		//Starts with "CP_" and Endswith "_Sig"
		if (element.first.find(start) != std::string::npos) {
			if (element.first.find(end) != std::string::npos)
			{
				Defs::ManipulationSignalHelperBoolean* found_manipul_signal = new Defs::ManipulationSignalHelperBoolean(element.first, element.second, offset, factor);
				helper_list.push_back(found_manipul_signal);
			}
		}
	}
	return helper_list;
}
*/
//std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationSignalHelperfloat*> EID::Net::ETH::GM_BEV3::Defs::generate_floatsigmanipulation_list(const std::string& start, const std::string& end, std::map<std::string, model_core::model::Signal*> moduloSignalList, float offset, float factor)
//{
//	std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationSignalHelperfloat*> helper_list;
//
//	for (auto element : moduloSignalList)
//	{
//		//Starts with "CP_" and Endswith "_Sig"
//		if (element.first.find(start) != std::string::npos) {
//			if (element.first.find(end) != std::string::npos)
//			{
//				Defs::ManipulationSignalHelperfloat* found_manipul_signal = new Defs::ManipulationSignalHelperfloat(element.first, element.second, offset, factor);
//				helper_list.push_back(found_manipul_signal);
//			}
//		}
//	}
//	return helper_list;
//}
