
#pragma once
#include <string>
#include "Global/Global.h"
//#include "NetManipulation/NM_FlexRay.h"
#include "ETH_Manipulation/ETH_Manipulation.h"
#include "ModelCore/Model/QuantitySignal.h"

using namespace model_core::model_access;

namespace EID
{
    namespace Net
    {
        namespace ETH
        {
            namespace GM_BEV3_205_9p9_V01_M
            {
                namespace Defs
                {
    /*
					class ManipulationHelper
					{
					public:
						ManipulationHelper(
							const std::string& SignalName,
							model_core::model::Signal* ManipulateCPSignalFlag,
							std::map<std::string, model_core::model::Signal*> moduloSignalList,
							const std::string& prefix, const std::string& postfix
						)
						{
							//postfix="_UB;"
							//assert(ManipulateCPSignalFlag);
							ManipFlag = ManipulateCPSignalFlag;
							name = SignalName;
							ManipSignalObj = ManipFlag->get_model_access_object();
							preset_obj = moduloSignalList[prefix + SignalName + postfix + "_Preset"]->get_model_access_object();
							modus_obj = moduloSignalList[prefix + SignalName + postfix + "_Modus"]->get_model_access_object();
							quantity_obj = moduloSignalList[prefix + SignalName + postfix + "_Quantity"]->get_model_access_object();
							value_obj = moduloSignalList[prefix + SignalName + postfix + "_Value"]->get_model_access_object();
							//preset_obj = moduloSignalList["CP_" + SignalName + "_UB_Preset"]->get_model_access_object();
							//modus_obj = moduloSignalList["CP_" + SignalName + "_UB_Modus"]->get_model_access_object();
							//quantity_obj = moduloSignalList["CP_" + SignalName + "_UB_Quantity"]->get_model_access_object();
							//value_obj = moduloSignalList["CP_" + SignalName + "_UB_Value"]->get_model_access_object();

							is_manipulated = get_is_manipulated();
							get_all_objects_value();
						}

						virtual ~ManipulationHelper() = default;

						std::string name;

						std::shared_ptr<ModelAccessObject> ManipSignalObj;
						model_core::model::Signal* ManipFlag; //Signal which enables/disable the Manipulation 

						bool is_manipulated;// = get_is_manipulated();
						unsigned old_value;

						std::shared_ptr<ModelAccessObject> preset_obj;
						std::shared_ptr<ModelAccessObject> modus_obj;
						std::shared_ptr<ModelAccessObject> quantity_obj;
						std::shared_ptr<ModelAccessObject> value_obj;
						unsigned tal_id;

						virtual void get_all_objects_value()
						{
							presett = preset_obj->get_boolean();
							moduss = modus_obj->get_unsigned();
							quantityy = quantity_obj->get_unsigned();
							valuee = value_obj->get_unsigned();

							//network_management->HandlePduTimeoutManipulation(rbsSession, manipp, presett, moduss, quantityy, valuee, pdu.second->Id);
						}

						virtual bool do_manipulation()
						{
							//Read manipulation flag at runtime
							//ManipSignalObj = ManipFlag->get_model_access_object();
							is_manipulated = get_is_manipulated();
							if (is_manipulated)
							{
								get_all_objects_value();
								if (
									presett != old_presett ||
									moduss != old_moduss ||
									quantityy != old_quantityy ||
									valuee != old_valuee
									) //compare old value and new value 
								{
									//network_management->HandlePduTimeoutManipulation(rbs_session, is_manipulated, presett, moduss, quantityy, valuee, tal_id);
									old_moduss = moduss;
									old_presett = presett;
									old_quantityy = quantityy;
									old_valuee = valuee;
								}
							}
							return true;
						}


						model_core::xil::A_BOOLEAN presett;
						model_core::xil::A_UINT64  moduss;
						model_core::xil::A_UINT64  quantityy;
						model_core::xil::A_UINT64  valuee;
						model_core::xil::A_BOOLEAN old_presett;
						model_core::xil::A_UINT64  old_moduss;
						model_core::xil::A_UINT64  old_quantityy;
						model_core::xil::A_UINT64  old_valuee;

					protected:
						bool get_is_manipulated() const
						{
							const bool result = ManipSignalObj->get_boolean();
							return result;
						}

					};
					
					class ManipulationHelperCheckSum : public ::EID::Net::ETH::GM_BEV3::Defs::ManipulationHelper
					{
					public:
						ManipulationHelperCheckSum(
							const std::string& SignalName,
							model_core::model::Signal* ManipulateCPSignalFlag,
							std::map<std::string, model_core::model::Signal*> moduloSignalList,
							const std::string& prefix, const std::string& postfix) : ManipulationHelper(
								SignalName, ManipulateCPSignalFlag,
								moduloSignalList, prefix, postfix), presettimer(0), old_presettimer(0)
						{
							presettimer_obj = moduloSignalList[prefix + SignalName + postfix + "_Preset_timer"]->
								get_model_access_object();
						}

						double presettimer;
						double old_presettimer;
						std::shared_ptr<ModelAccessObject> presettimer_obj = nullptr;

						void get_all_objects_value() override
						{
							ManipulationHelper::get_all_objects_value();
							presettimer = presettimer_obj->get_float();
						}

						bool do_manipulation() override
						{
							//Read manipulation flag at runtime
							ManipSignalObj = ManipFlag->get_model_access_object();
							is_manipulated = get_is_manipulated();
							if (is_manipulated)
							{
								ManipulationHelper::get_all_objects_value();
								if (
									presett != old_presett ||
									moduss != old_moduss ||
									quantityy != old_quantityy ||
									valuee != old_valuee ||
									presettimer != old_presettimer
									) //compare old value and new value 
								{
									//network_management->HandleChecksumManipulation(rbs_session, is_manipulated, presett, moduss,quantityy, valuee, presettimer, tal_id);
									old_moduss = moduss;
									old_presett = presett;
									old_quantityy = quantityy;
									old_valuee = valuee;
									old_presettimer = presettimer;
								}
							}
							return true;
						}
					};

					class ManipulationHelperCounter : public ::EID::Net::ETH::GM_BEV3::Defs::ManipulationHelper
					{
					public:
						ManipulationHelperCounter(
							std::string SignalName,
							model_core::model::Signal* ManipulateCPSignalFlag,
							std::map<std::string, model_core::model::Signal*> moduloSignalList,
							const std::string& prefix, const std::string& postfix) : ManipulationHelper(
								SignalName, ManipulateCPSignalFlag,
								moduloSignalList, prefix, postfix), presettimer(0), old_presettimer(0)
						{
							presettimer_obj = moduloSignalList[prefix + SignalName + postfix + "_Preset_timer"]->
								get_model_access_object();
						}

						double presettimer;
						double old_presettimer;
						std::shared_ptr<ModelAccessObject> presettimer_obj = nullptr;

						void get_all_objects_value() override
						{
							ManipulationHelper::get_all_objects_value();
							presettimer = presettimer_obj->get_float();
						}

						bool do_manipulation() override
						{
							//Read manipulation flag at runtime
							ManipSignalObj = ManipFlag->get_model_access_object();
							is_manipulated = get_is_manipulated();
							if (is_manipulated)
							{
								ManipulationHelper::get_all_objects_value();
								if (
									presett != old_presett ||
									moduss != old_moduss ||
									quantityy != old_quantityy ||
									valuee != old_valuee ||
									presettimer != old_presettimer
									) //compare old value and new value 
								{
									//network_management->HandleChecksumManipulation(rbs_session, is_manipulated, presett, moduss,quantityy, valuee, presettimer, tal_id);
									old_moduss = moduss;
									old_presett = presett;
									old_quantityy = quantityy;
									old_valuee = valuee;
									old_presettimer = presettimer;
								}
							}
							return true;
						}
					};

					class ManipulationSignalHelperBoolean
					{
					public:
						ManipulationSignalHelperBoolean(
							const std::string& SignalName,
							model_core::model::Signal* ManipulateCPSignal
						)
						{
							name = SignalName;
							SignalObj = ManipulateCPSignal;
							ManipSignalObj = SignalObj->get_model_access_object();
							new_value = SignalObj->get_model_access_object()->get_boolean();
							old_value = SignalObj->get_model_access_object()->get_boolean();
						}

						~ManipulationSignalHelperBoolean() = default;

						//bool is_manipulated;
						std::string name;
						float offsetval;
						float factorval;
						std::shared_ptr<ModelAccessObject> ManipSignalObj;
						model_core::model::Signal* SignalObj; //Signal Manipulation 

						bool new_value;
						bool old_value;
						unsigned tal_id;
						//TAL_SessionHandleType rbs_session;
						//shared_ptr<NM> network_management = nullptr;

						bool do_manipulation()
						{
							//Read new value at runtime
							new_value = ManipSignalObj->get_boolean();
							//is_manipulated = get_is_manipulated();
							if (old_value != new_value)
							{
								//network_management->SendSignal(rbs_session, tal_id, new_value, factorval, offsetval);
								old_value = new_value;
							}
							return true;
						}
					};
					*/
    class ManipulationSignalHelperfloat
    {
    public:
    ManipulationSignalHelperfloat(
    const std::string& SignalName,
    model_core::model::Signal* ManipulateCPSignal)
    {
    name = SignalName;
    SignalObj = ManipulateCPSignal;
    ManipSignalObj = SignalObj->get_model_access_object();
    new_value = SignalObj->get_model_access_object()->get_float();
    old_value = SignalObj->get_model_access_object()->get_float();
    }

    ~ManipulationSignalHelperfloat() = default;

    std::string name;
    float offsetval;
    float factorval;
    std::shared_ptr<ModelAccessObject> ManipSignalObj;
    model_core::model::Signal* SignalObj; //Signal Manipulation 

    model_core::xil::A_FLOAT64 new_value;
    model_core::xil::A_FLOAT64 old_value;
    unsigned tal_id;
    //TAL_SessionHandleType rbs_session;
    //shared_ptr<NM> network_management = nullptr;

    bool do_manipulation()
    {
    //Read new value at runtime
    new_value = ManipSignalObj->get_float();
    if (old_value != new_value)
    {
        //network_management->SendSignal(rbs_session, tal_id, new_value, factorval, offsetval);
        old_value = new_value;
    }
    return true;
    }
    };

    //DLL_EXPORT std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationHelper*> generate_pdumanipulation_list(const std::string& start, const std::string& end, std::map<std::string, model_core::model::Signal*> moduloSignalList);
    //DLL_EXPORT std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationHelperCheckSum*> generate_checksummanipulation_list(const std::string& start, const std::string& end, std::map<std::string, model_core::model::Signal*> moduloSignalList);
    //DLL_EXPORT std::vector<EID::Net::ETH::GM_BEV3::Defs::ManipulationHelperCounter*> generate_countermanipulation_list(const std::string& start, const std::string& end, std::map<std::string, model_core::model::Signal*> moduloSignalList);
                } // END OF NAMESPACE: Defs
            } // END OF NAMESPACE: GM_BEV3_205_9p9_V01_M
        } // END OF NAMESPACE: ETH
    } // END OF NAMESPACE: Net
} // END OF NAMESPACE: EID
