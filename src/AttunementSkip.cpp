#include "AttunementSkip.h"

AttunementSkip* AttunementSkip::instance()
{
    static AttunementSkip instance;
    return &instance;
}

void AttunementSkip::LoadConfig()
{
    enabled = sConfigMgr->GetOption<bool>("AttunementSkip.Enable", true);

    grantDrakefireAmulet = sConfigMgr->GetOption<bool>("AttunementSkip.DrakefireAmulet", true);
    grantOnyxiaScaleCloak = sConfigMgr->GetOption<bool>("AttunementSkip.OnyxiaScaleCloak", true);
    grantKeyToKarazhan = sConfigMgr->GetOption<bool>("AttunementSkip.KeyToKarazhan", true);
    grantTempestKey = sConfigMgr->GetOption<bool>("AttunementSkip.TempestKey", true);
    grantMedallionOfKarabor = sConfigMgr->GetOption<bool>("AttunementSkip.MedallionOfKarabor", true);

    completeNaxx40Attunement = sConfigMgr->GetOption<bool>("AttunementSkip.Naxx40Attunement", true);
    completeCudgelOfKarDesh = sConfigMgr->GetOption<bool>("AttunementSkip.CudgelOfKarDesh", true);
    completeVialsOfEternity = sConfigMgr->GetOption<bool>("AttunementSkip.VialsOfEternity", true);
}

class AttunementSkip_WorldScript : public WorldScript
{
public:
    AttunementSkip_WorldScript() : WorldScript("AttunementSkip_WorldScript") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        sAttunementSkip->LoadConfig();
    }
};

void AddSC_AttunementSkip()
{
    new AttunementSkip_WorldScript();
}
