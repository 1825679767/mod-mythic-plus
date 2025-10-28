/*
 * Credits: silviu20092
 */

#include "ScriptMgr.h"
#include "GameTime.h"
#include "mythic_plus.h"

class mythic_plus_playerscript : public PlayerScript
{
public:
    mythic_plus_playerscript() : PlayerScript("mythic_plus_playerscript",
        {
            PLAYERHOOK_ON_LOGIN,
            PLAYERHOOK_ON_PLAYER_JUST_DIED
        }
    )
    {
    }

    void OnPlayerLogin(Player* player) override
    {
        if (!sMythicPlus->IsEnabled())
            return;

        // 初始化玩家的史诗钥石等级（如果是新玩家，设置为1级）
        sMythicPlus->InitializePlayerMythicLevel(player);

        // check if the saved M+ level is still present (maybe it was removed from DB in the meantime)
        uint32 playerMplusLevel = sMythicPlus->GetCurrentMythicPlusLevel(player);
        if (playerMplusLevel > 0 && !sMythicPlus->GetMythicLevel(playerMplusLevel))
            sMythicPlus->SetCurrentMythicPlusLevel(player, 1, true); // force reset the level to 1

        Group* group = player->GetGroup();
        if (group != nullptr)
        {
            ObjectGuid leaderGuid = group->GetLeaderGUID();
            uint32 mplusLevel = sMythicPlus->GetCurrentMythicPlusLevelForGUID(leaderGuid.GetCounter());
            if (mplusLevel > 0)
                MythicPlus::BroadcastToPlayer(player, "你的队长（可能就是你）当前的史诗钥石等级为 " + Acore::ToString(mplusLevel) + " 级。队长可以使用史诗钥石开启挑战！");
        }
    }

    void OnPlayerJustDied(Player* player) override
    {
        if (player && sMythicPlus->IsInMythicPlus(player))
        {
            MythicPlus::MapData* mapData = sMythicPlus->GetMapData(player->GetMap(), false);
            ASSERT(mapData);

            if (mapData->penaltyOnDeath > 0 && !mapData->done)
            {
                std::ostringstream oss;
                oss << player->GetName() << " 刚刚阵亡，计时增加了 ";
                oss << secsToTimeString(mapData->penaltyOnDeath);
                oss << "。";

                Map* map = player->GetMap();
                sMythicPlus->BroadcastToMap(player->GetMap(), MythicPlus::Utils::RedColored(oss.str()));

                mapData->deaths++;
                
                sMythicPlus->SaveDungeonInfo(map->GetInstanceId(), map->GetId(), mapData->timeLimit, mapData->mythicPlusStartTimer, mapData->mythicLevel->level, mapData->penaltyOnDeath, mapData->deaths, mapData->done);
            }
        }
    }
};

void AddSC_mythic_plus_playerscript()
{
    new mythic_plus_playerscript();
}
