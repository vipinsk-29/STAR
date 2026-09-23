#pragma once

#include "Base/ETH1Base.h"
#include "Global/Global.h"

#include "XmlSignalReader/XmlSignalReader.h"
#include "Defs/ModelData.h"
#include "Defs/ManipHelperClass.h"
#include "Global/macros.h"

#include <unordered_map>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <map>

using namespace model_core::model_access;
namespace HwLight = Plugins::FlexCard3::PC_HW_Interface::Light;
namespace HwSerializer = Plugins::FlexCard3::PC_HW_Interface::Light::HwSerializer;

namespace EID
{
	namespace Net
	{
		namespace ETH
		{
			namespace GM_BEV3_205_9p9_V01_M
			{
				class DLL_EXPORT_COMPONENT ETH1Core : public ::EID::Net::ETH::GM_BEV3_205_9p9_V01_M::ETH1Base
				{
				public:
					std::string nodeName = "";
					const std::string STAR_PREFIX{ "FC3: " };
					uint32_t cardNumber = 1;
					u08 wait = 0;
					bool success;
					bool WuP_Cyclic_Control = false;
					bool Init = false;

					HwLight::HwComDataObject<void, 0> read_Index{ 0 };
					uint16_t readSlot_Index = 0;

					// ETH1 Frames HwComDataObjects
					HwLight::HwComDataObject<void, 0> ETH1_Frame_WuP{ 0 };
					HwLight::HwComDataObject<void, 0> ETH1_Frame_Heartbeat{ 0 };
					HwLight::HwComDataObject<void, 0> ETH1_Frame_Info{ 0 };

					// ETH1 PDUs HwComDataObjects
					HwLight::HwComDataObject<void, 36> ETH1_PDU_WuP{ 0 };
					HwLight::HwComDataObject<void, 18> ETH1_PDU_Heartbeat{ 0 };
					HwLight::HwComDataObject<void, 28> ETH1_PDU_Info{ 0 };

					// ETH1 Custom Timings
					HwLight::HwComDataObject<uint32_t, sizeof(uint32_t)> ETH1_Custom_Timing_WuP{ 0 };
					HwLight::HwComDataObject<uint32_t, sizeof(uint32_t)> ETH1_Custom_Timing_Heartbeat{ 0 };
					HwLight::HwComDataObject<uint32_t, sizeof(uint32_t)> ETH1_Custom_Timing_Info{ 0 };

					// Global Variable HwComDataObjects (address set from XML)
					HwLight::HwComDataObject<uint8_t, 1> gVarAlternativeTiming{ 0 };
					HwLight::HwComDataObject<uint8_t, 1> gVarAlternativeTimingEth1{ 0 };
					HwLight::HwComDataObject<uint8_t, 1> gVarAlternativeTimingEth2{ 0 };
					HwLight::HwComDataObject<uint8_t, 1> gVarFcCounterValueSetAll{ 0 };
					HwLight::HwComDataObject<uint8_t, 1> gVarIgnitionState{ 0 };
					HwLight::HwComDataObject<uint8_t, 1> gVarSaveFreshnessAll{ 0 };
					HwLight::HwComDataObject<uint8_t, 1> gVarService3163Rcvd{ 0 };
					HwLight::HwComDataObject<uint8_t, 1> gVarService3164Rcvd{ 0 };
					HwLight::HwComDataObject<uint8_t, 1> gVarSetFreshnessAll{ 0 };
					HwLight::HwComDataObject<uint8_t, 1> gVarSetWuP{ 0 };

					// ETH1 Signals HwComDataObjects
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstTransSIP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_M_eBstTotAxlTrqActP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstFuncTstAllwdP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_p_eBstBrkTgtRrP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_phi_eBstStrWhlAngP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstActrModeRfP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstBrkCmdTypeLfP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstOAT_InvP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_v_eBstWhlSpdRfP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_I_eBstPwrMgmtSinkLimP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstWhlSpdLfInvP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_a_eBstVehAyP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_p_eBstBrkTgtLfP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstRmtPrgActvP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_T_eBstOAT_CorrP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstBrkCmdTypeRrP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_p_eBstBrkTgtRfP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_I_eBstPwrMgmtGenLimP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstActrModeLfP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_v_eBstWhlSpdLfP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_v_eBstWhlSpdRrP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_e_eBstEPB_CmdP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_F_eBstEPB_StateCmdLtP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_e_eBstBrkSysPwrModeP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstActrModeLrP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstHydFuncStCmdP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_b_eBstPwrMgmtReqP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_Pct_eBstAccelEffPosP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_a_eBstVeh_AxP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_F_eBstEPB_StateCmdRtP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstWhlSpdRrInvP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstActrModeRrP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstWhlSpdRfInvP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstVeh_AxInvP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_l_eBstVehOdoBCM_P_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstBrkCmdTypeRfP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstWhlSpdLrInvP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstBrkCmdTypeLrP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_v_eBstWhlSpdLrP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_p_eBstBrkTgtLrP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_e_eBstTransLvrPstnP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstWrmUpCyclCmptP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstRnCrnkActBkupP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_e_eBstPriPwrModeP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstRnCrnkActPriP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_e_eBstBkupPwrModeP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_y_eBstVehRegionCodeP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_PropSysActvP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_v_eBstVehicleP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_V_eBstRplnshVolTrgtP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_p_eBstBkPrsTgtBaseP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1SSMR_0C598001_0CD68001_QoS_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1YeBACR_e_eBstBrkOprtnRqstP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1NeBACR_b_eBstBrkFdSt2DiagP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1NeBACR_t_eBstPropSysInactvP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_b_eBstEPB_HpoAvailP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1VeBACR_e_eBstRplnshTriggerP_Signal{ 0 };
					HwLight::HwComDataObject<double, 8> eth1NeBACR_b_eBstBrkFdSt1DiagP_Signal{ 0 };

					// Generic processing helpers
					std::unordered_map<std::string, std::reference_wrapper<decltype(eth1VeBACR_b_eBstTransSIP_Signal)>> eth1HwSignalMap;
					std::unordered_map<std::string, double> eth1OldPhysValueMap;

					// Standard Interface
					std::shared_ptr<Plugins::FlexCard3::PC_HW_Interface::PC_HW_Int_Base::PC_HW_Int_Base> pc_hw_int = nullptr;
					std::shared_ptr<Plugins::FlexCard3::PC_HW_Interface::PC_HW_Int_V100::PC_HW_Int_V100> pc_hw_interface = nullptr;
					std::shared_ptr<Plugins::FlexCard3::PC_HW_Interface::Light::PC_HW_Int_Light::PC_HW_Int_Light> pc_hw_interface_light = nullptr;

					Plugins::FlexCard3::ETH_Manipulation::ETH_Manipulation* helper = Plugins::FlexCard3::ETH_Manipulation::ETH_Manipulation::getInstance();

					t_hw_com_light_value WakeUpValues2Set[2] = {};
					t_hw_com_light_value HeartBeatValues2Set[2] = {};
					t_hw_com_light_value InfoValues2Set[2] = {};
					HW_COM_LIGHT_PHYS_DATA AltTimingSetValue[2] = {};

					const std::string HeartBeat_VLAN_111_PDU = "PDU_SYS_PMMulticastRxPwrMgrMulti_Heartbeat";
					const std::string WakeUp_VLAN_111_PDU = "PDU_SYS_PMMulticastRxPwrMgrMulti_Wakeup";
					const std::string Info_PDU = "PDU_SYS_SMUnicastRxMechatronicsT1S_Info";

					const std::string WakeUp_VLAN_111_Frame_Tx = "PDU_SYS_PMMulticastRxPwrMgrMulti_Wakeup";
					const std::string HeartBeat_VLAN_111_Frame_Tx = "SPDU_SYS_PMMulticastRxPwrMgrMulti_Heartbeat";
					const std::string Info_Frame_Tx = "SPDU_SYS_SMUnicastRxMechatronicsT1S_Info";

					void SignalListData();
					void PDUListData();
					void FRAMEListData();
					void GlobalVars_list();

				protected:
					Plugins::Global::Global globalPlugin;
					double cycleTimer;
					double cycleTimeWuPTickCount;
					double cycleTimeWuPInitTickCount;
					double cycleTimeHBTickCount;
					double cycleTimeInfoTickCount;
					double cycleTimeSomeIPTickCount;
					bool Info_activation = false;

					std::map<std::string, model_core::model::Signal*> moduloSignalList;
					std::vector<std::unique_ptr<Defs::ManipulationSignalHelperfloat>> FloatSigManipulationHelperList;

					std::map<std::string, unsigned int> FrameManipList;
					std::map<std::string, std::shared_ptr<IdValuePair<double>>> FrameList;
					std::map<std::string, SignalDataProcessing::Frame> sendFrameList;

					std::map<std::string, unsigned int> PDUManipList;
					std::map<std::string, unsigned int> PDULengthList;
					std::map<std::string, std::shared_ptr<IdValuePair<double>>> PDUSetList;
					std::map<std::string, std::shared_ptr<IdValuePair<double>>> PDUGetList;
					std::map<std::string, SignalDataProcessing::PDU> sendPDUList;
					std::map<std::string, SignalDataProcessing::PDU> receivePDUList;

					std::map<std::string, unsigned int> signalGetRawList;
					std::map<std::string, unsigned int> signalLenRawList;
					std::map<std::string, unsigned int> signalSetRawList;

					std::map<std::string, unsigned int> signalGetphysList;
					std::map<std::string, unsigned int> signalLenphysList;
					std::map<std::string, unsigned int> signalSetphysList;

					std::map<std::string, unsigned int> gVarLengthList;
					std::map<std::string, unsigned int> gVarSetList;
					std::map<std::string, unsigned int> gVarGetList;

					std::map<std::string, SignalDataProcessing::Signal> sendSignalsList_Raw;
					std::map<std::string, SignalDataProcessing::Signal> sendSignalsList_Phys;

					std::map<std::string, std::shared_ptr<IdValuePair<double>>> signalList_float_Phys;
					std::map<std::string, std::shared_ptr<IdValuePair<bool>>> signalList_bool_Phys;
					std::map<std::string, std::shared_ptr<IdValuePair<double>>> signalList_float_Raw;
					std::map<std::string, std::shared_ptr<IdValuePair<bool>>> signalList_bool_Raw;
					std::map<std::string, std::shared_ptr<IdValuePair<double>>> gVarList_Phys;


					//Length = 36
					std::vector<uint8_t> setRawPduWakeUpBuffer_V22 = {
						0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x00,
						0x0A, 0x16, 0x01, 0x81, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
						0x00, 0x00, 0x00, 0x00
					};
					//Length = 18
					std::vector<uint8_t> setRawPduHBBuffer_V22 = {
						0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x00,
						0x0A, 0x16, 0x01, 0x81, 0x00, 0x00, 0x00, 0x00,
						0x00, 0x00
					};
					//Length = 28
					std::vector<uint8_t> setRawPduInfoBuffer_V22 = {
						0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x00,
						0x0A, 0x16, 0x01, 0x81, 0x0A, 0x16, 0x06, 0x21,
						0x00, 0x00, 0x06, 0x0C, 0x5B, 0x00, 0x01, 0x00,
						0x01, 0x01, 0x00, 0x00
					};

					void InitializeAllLists();

				private:
					void initialize();
					void uninitialize();

					DEFINE_COMPONENT_CORE_IMPLEMENTATION(ETH1)
				};
			}
		}
	}
}