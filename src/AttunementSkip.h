#ifndef AZEROTHCORE_ATTUNEMENTSKIP_H
#define AZEROTHCORE_ATTUNEMENTSKIP_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Mail.h"
#include "Chat.h"
#include "Item.h"
#include "ObjectMgr.h"

enum AttunementItems
{
    ITEM_DRAKEFIRE_AMULET      = 16309,
    ITEM_ONYXIA_SCALE_CLOAK    = 15138,
    ITEM_KEY_TO_KARAZHAN       = 24490,
    ITEM_TEMPEST_KEY           = 31704,
    ITEM_MEDALLION_OF_KARABOR  = 32649
};

enum AttunementQuests
{
    QUEST_NAXX40_ATTUNEMENT_1 = 9121,  // The Archangel's Payload
    QUEST_NAXX40_ATTUNEMENT_2 = 9122,  // Echoes of War
    QUEST_NAXX40_ATTUNEMENT_3 = 9123,  // The Only Song I Know...
    QUEST_CUDGEL_OF_KARDESH   = 10901, // The Cudgel of Kar'desh
    QUEST_VIALS_OF_ETERNITY   = 10445  // The Vials of Eternity
};

enum AttunementLevelThresholds
{
    LEVEL_CLASSIC_RAIDS = 60,
    LEVEL_TBC_RAIDS     = 70
};

class AttunementSkip
{
public:
    static AttunementSkip* instance();

    bool enabled;
    bool grantDrakefireAmulet;
    bool grantOnyxiaScaleCloak;
    bool grantKeyToKarazhan;
    bool grantTempestKey;
    bool grantMedallionOfKarabor;
    bool completeNaxx40Attunement;
    bool completeCudgelOfKarDesh;
    bool completeVialsOfEternity;

    void LoadConfig();
    void ProcessPlayerLevel(Player* player);

private:
    bool PlayerHasItem(Player* player, uint32 itemId);
    void SendAttunementMail(Player* player, std::vector<std::pair<uint32, bool>> const& items, uint8 levelThreshold);
    void AutoCompleteQuest(Player* player, uint32 questId);
};

#define sAttunementSkip AttunementSkip::instance()

#endif // AZEROTHCORE_ATTUNEMENTSKIP_H
