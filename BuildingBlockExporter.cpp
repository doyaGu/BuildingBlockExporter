#include <iostream>

#include "BuildingBlock.h"

#include "MinHook.h"

std::vector<std::string> g_BuildingBlockDlls;

CKERROR GetBehaviorGuidsFromPlugin(CKSTRING plugin, XArray<CKGUID> &guids)
{
    CKPluginManager *pm = CKGetPluginManager();
    CKERROR res = pm->RegisterPlugin(plugin);
    if (res != CK_OK)
        return res;

    int pluginCount = pm->GetPluginCount(CKPLUGIN_BEHAVIOR_DLL);
    int pluginIdx;
    CKPluginEntry *pluginInfo = nullptr;
    for (pluginIdx = 0; pluginIdx < pluginCount; ++pluginIdx)
    {
        pluginInfo = pm->GetPluginInfo(CKPLUGIN_BEHAVIOR_DLL, pluginIdx);
        CKPluginDll *pluginDll = pm->GetPluginDllInfo(pluginInfo->m_PluginDllIndex);
        if (pluginDll->m_DllFileName == plugin)
            break;
    }
    if (pluginIdx >= pluginCount)
        return CKERR_NOTFOUND;

    guids = pluginInfo->m_BehaviorsInfo->m_BehaviorsGUID;
    return CK_OK;
}

static void DumpBuildingBlocks(const std::string &dllname, const XArray<CKGUID> &guids)
{
    for (auto it = guids.Begin(); it != guids.End(); ++it)
    {
        BuildingBlock bb(*it);
        bb.Load();
        bb.Dump("", dllname.substr(0, dllname.size() - (dllname.size() - dllname.rfind('.'))).c_str());
    }
}

static bool HookCreateCKBehaviorPrototypeRuntime()
{
    VxSharedLibrary sl;
    sl.Attach(GetModuleHandle("CK2.dll"));
    LPVOID lpCreateCKBehaviorPrototypeRunTimeProc = sl.GetFunctionPtr(
        const_cast<CKSTRING>("?CreateCKBehaviorPrototypeRunTime@@YAPAVCKBehaviorPrototype@@PAD@Z"));
    LPVOID lpCreateCKBehaviorPrototypeProc = sl.GetFunctionPtr(
        const_cast<CKSTRING>("?CreateCKBehaviorPrototype@@YAPAVCKBehaviorPrototype@@PAD@Z"));
    if (MH_CreateHook(lpCreateCKBehaviorPrototypeRunTimeProc, lpCreateCKBehaviorPrototypeProc, NULL) != MH_OK ||
        MH_EnableHook(lpCreateCKBehaviorPrototypeRunTimeProc) != MH_OK)
    {
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (MH_Initialize() != MH_OK)
        return -1;
    if (!HookCreateCKBehaviorPrototypeRuntime())
        return -1;

    if (argc < 2)
    {
        std::cout << "usage: " << argv[0] << " building block dlls" << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i)
    {
        g_BuildingBlockDlls.emplace_back(argv[i]);
    }

    if (CKStartUp() != CK_OK)
    {
        std::cout << "Initialisation Error: Unable to startup Virtools Engine" << std::endl;
        return -1;
    }

    for (const auto &dll : g_BuildingBlockDlls)
    {
        XArray<CKGUID> guids;
        CKERROR res = GetBehaviorGuidsFromPlugin(const_cast<CKSTRING>(dll.c_str()), guids);
        switch (res)
        {
        case CK_OK:
            DumpBuildingBlocks(dll, guids);
            break;
        case CKERR_INVALIDPLUGIN:
        case CKERR_NOTFOUND:
            std::cout << "Error: " << dll << " is not behavior dll" << std::endl;
            return -1;
        default:
            std::cout << "Unknown Error" << std::endl;
            return -1;
        }
    }

    if (MH_Uninitialize() != MH_OK)
        return -1;

    return 0;
}