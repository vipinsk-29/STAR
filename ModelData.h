
#pragma once
#include <ModelCore/Platform.h>
#include <string>
#include <map>
#include <memory>

static bool registerReceiveSignals = false;
static bool isReadxmlDone = false;

template<typename T>
struct IdValuePair
{
   public:
       T OldValue;
       uint64_t Id = 0;
       uint16_t Length = 0;
       std::string Name = "";
};

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
                class DLL_EXPORT_COMPONENT ModelData
                {
                    public:
                        ModelData();
                        ~ModelData();
                };
                } // END OF NAMESPACE: Defs
            } // END OF NAMESPACE: GM_BEV3_205_9p9_V01_M
        } // END OF NAMESPACE: ETH
    } // END OF NAMESPACE: Net
} // END OF NAMESPACE: EID
