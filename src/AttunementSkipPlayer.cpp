#include "AttunementSkip.h"

class AttunementSkip_PlayerScript : public PlayerScript
{
public:
    AttunementSkip_PlayerScript() : PlayerScript("AttunementSkip_PlayerScript") { }

    void OnPlayerLogin(Player* player) override
    {
        if (!sAttunementSkip->enabled)
            return;

        if (!player || !player->IsInWorld())
            return;

        sAttunementSkip->ProcessPlayerLevel(player);
    }

    void OnPlayerLevelChanged(Player* player, uint8 /*oldLevel*/) override
    {
        if (!sAttunementSkip->enabled)
            return;

        if (!player || !player->IsInWorld())
            return;

        sAttunementSkip->ProcessPlayerLevel(player);
    }
};

void AttunementSkip::ProcessPlayerLevel(Player* player)
{
    uint8 level = player->GetLevel();

    // Level 60: Classic raid attunements
    if (level >= LEVEL_CLASSIC_RAIDS)
    {
        // Send classic attunement items
        std::vector<std::pair<uint32, bool>> classicItems = {
            { ITEM_DRAKEFIRE_AMULET,   grantDrakefireAmulet },
            { ITEM_ONYXIA_SCALE_CLOAK, grantOnyxiaScaleCloak }
        };

        SendAttunementMail(player, classicItems, LEVEL_CLASSIC_RAIDS);

        // Auto-complete Naxx40 attunement quests
        if (completeNaxx40Attunement)
        {
            AutoCompleteQuest(player, QUEST_NAXX40_ATTUNEMENT_1);
            AutoCompleteQuest(player, QUEST_NAXX40_ATTUNEMENT_2);
            AutoCompleteQuest(player, QUEST_NAXX40_ATTUNEMENT_3);
        }
    }

    // Level 70: TBC raid attunements
    if (level >= LEVEL_TBC_RAIDS)
    {
        // Send TBC attunement items
        std::vector<std::pair<uint32, bool>> tbcItems = {
            { ITEM_KEY_TO_KARAZHAN,      grantKeyToKarazhan },
            { ITEM_TEMPEST_KEY,          grantTempestKey },
            { ITEM_MEDALLION_OF_KARABOR, grantMedallionOfKarabor }
        };

        SendAttunementMail(player, tbcItems, LEVEL_TBC_RAIDS);

        // Auto-complete TBC attunement quests
        if (completeCudgelOfKarDesh)
            AutoCompleteQuest(player, QUEST_CUDGEL_OF_KARDESH);

        if (completeVialsOfEternity)
            AutoCompleteQuest(player, QUEST_VIALS_OF_ETERNITY);
    }
}

bool AttunementSkip::PlayerHasItem(Player* player, uint32 itemId)
{
    if (!player)
        return false;

    // Check inventory and bank
    if (player->HasItemCount(itemId, 1, true))
        return true;

    // Check mail inbox for the item
    for (Mail* m : player->GetMails())
    {
        if (m->state == MAIL_STATE_UNCHANGED || m->state == MAIL_STATE_CHANGED)
        {
            for (auto const& itemInfo : m->items)
            {
                if (itemInfo.item_template == itemId)
                    return true;
            }
        }
    }

    return false;
}

void AttunementSkip::SendAttunementMail(Player* player, std::vector<std::pair<uint32, bool>> const& items, uint8 levelThreshold)
{
    std::vector<uint32> itemsToSend;

    for (auto const& [itemId, enabled] : items)
    {
        if (!enabled)
            continue;

        if (!PlayerHasItem(player, itemId))
            itemsToSend.push_back(itemId);
    }

    if (itemsToSend.empty())
        return;

    // Build mail
    std::string subject = "Your Attunement Items";
    std::string body = "Greetings,\n\nAs you have reached level " + std::to_string(levelThreshold) + ", you have been granted the following attunement items to access raid content:\n\n";

    for (uint32 itemId : itemsToSend)
    {
        ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(itemId);
        if (itemProto)
            body += "- " + std::string(itemProto->Name1) + "\n";
    }

    body += "\nThese items are required for raid entry. Good luck!\n";

    MailDraft draft(subject, body);

    for (uint32 itemId : itemsToSend)
    {
        Item* item = Item::CreateItem(itemId, 1, player);
        if (item)
            draft.AddItem(item);
    }

    CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
    MailSender sender(MAIL_NORMAL, 0, MAIL_STATIONERY_GM);
    draft.SendMailTo(trans, MailReceiver(player), sender, MAIL_CHECK_MASK_HAS_BODY, 0);
    CharacterDatabase.CommitTransaction(trans);
}

void AttunementSkip::AutoCompleteQuest(Player* player, uint32 questId)
{
    if (!player || !player->IsInWorld())
        return;

    // Skip if already rewarded
    if (player->GetQuestStatus(questId) == QUEST_STATUS_REWARDED)
        return;

    Quest const* quest = sObjectMgr->GetQuestTemplate(questId);
    if (!quest)
        return;

    // If quest is not taken, add it
    if (player->GetQuestStatus(questId) == QUEST_STATUS_NONE)
    {
        player->AddQuest(quest, nullptr);
    }

    // Complete and reward the quest
    if (player->GetQuestStatus(questId) != QUEST_STATUS_REWARDED)
    {
        player->RewardQuest(quest, 0, player, false, false);
    }
}

void AddSC_AttunementSkip_Player()
{
    new AttunementSkip_PlayerScript();
}
