/*
 * Credits: silviu20092
 */

#include "ScriptMgr.h"
#include "GameTime.h"
#include "mythic_affix.h"
#include "mythic_plus.h"

class mythic_plus_all_mapscript : public AllMapScript
{
private:
    std::unordered_map<uint32, uint32> instanceTimer;
public:
    mythic_plus_all_mapscript() : AllMapScript("mythic_plus_all_mapscript",
        {
            ALLMAPHOOK_ON_PLAYER_ENTER_ALL,
            ALLMAPHOOK_ON_MAP_UPDATE,
            ALLMAPHOOK_ON_DESTROY_INSTANCE
        })
    {
    }

    void OnPlayerEnterAll(Map* map, Player* player) override
    {
        const MythicPlus::MythicPlusDungeonInfo* savedDungeon = sMythicPlus->GetSavedDungeonInfo(map->GetInstanceId());

        // edge case when players were in a M+ dungeon, server was restarted and the system was disabled in the meantime
        if (!sMythicPlus->IsEnabled() && map->GetInstanceId() != 0)
        {
            if (savedDungeon != nullptr)
            {
                if (savedDungeon->mythicLevel > 0)
                {
                    MythicPlus::BroadcastToPlayer(player, "尝试加入已保存的史诗钥石副本，但系统现已停用。");
                    MythicPlus::FallbackTeleport(player);
                    return;
                }
            }
            else
            {
                // save even non Mythic Plus dungeon in DB, this is required for further edge checks
                if (sMythicPlus->MatchMythicPlusMapDiff(map))
                    sMythicPlus->SaveDungeonInfo(map->GetInstanceId(), map->GetId(), 0, 0L, 0, 0, 0, false, false);
            }
        }

        if (sMythicPlus->CanMapBeMythicPlus(map))
        { 
            if (savedDungeon != nullptr)
            {
                if (!savedDungeon->isMythic)
                    return; // don't care about regular dungeons

                const MythicLevel* mythicLevel = sMythicPlus->GetMythicLevel(savedDungeon->mythicLevel);
                if (savedDungeon->mythicLevel > 0 && mythicLevel == nullptr)
                {
                    // edge case where a dungeon was saved as M+ but now the level does not longer exist (removed from DB)
                    MythicPlus::BroadcastToPlayer(player, "该副本曾保存为史诗钥石，但对应的层数已不存在。");
                    MythicPlus::FallbackTeleport(player);
                    return;
                }

                if (mythicLevel == nullptr)
                    return;

                if (player->GetLevel() < DEFAULT_MAX_LEVEL)
                {
                    MythicPlus::BroadcastToPlayer(player, "加入史诗钥石副本需要达到最高等级。");
                    MythicPlus::FallbackTeleport(player);
                    return;
                }

                MythicPlus::MapData* mapData = sMythicPlus->GetMapData(map);
                mapData->mythicPlusStartTimer = savedDungeon->startTime;
                mapData->done = savedDungeon->done;
                mapData->timeLimit = savedDungeon->timeLimit;
                mapData->deaths = savedDungeon->deaths;
                mapData->penaltyOnDeath = savedDungeon->penaltyOnDeath;

                if (!mapData->mythicLevel)
                {
                    MythicPlus::BroadcastToPlayer(player, "你刚加入一个史诗钥石副本，所有词缀已为本实例设置并保存。");
                    mapData->mythicLevel = mythicLevel;
                }
                else
                    MythicPlus::BroadcastToPlayer(player, "你加入了一个正在进行的史诗钥石副本，所有词缀已设置并生效。");

                sMythicPlus->PrintMythicLevelInfo(mapData->mythicLevel, player);

                std::ostringstream oss;
                if (!mapData->done)
                {
                    long long diff = GameTime::GetGameTime().count() - mapData->mythicPlusStartTimer;
                    mapData->updateTimer = diff * 1000;
                    if (diff + mapData->GetPenaltyTime() <= mapData->timeLimit)
                    {
                        oss << "史诗钥石副本正在进行。当前计时：";
                        oss << secsToTimeString(diff);
                        oss << "。在此时间内完成即可获得战利品：";
                        oss << secsToTimeString(mapData->timeLimit);
                    }
                    else
                    {
                        oss << "史诗钥石副本正在进行，但无法获得战利品。";
                        oss << " 限定时间：" << secsToTimeString(mapData->timeLimit);
                        oss << "。当前计时：" << secsToTimeString(diff);
                        mapData->receiveLoot = false;
                    }

                    if (mapData->penaltyOnDeath > 0)
                    {
                        std::ostringstream oss2;
                        oss2 << "死亡将带来时间惩罚：";
                        oss2 << secsToTimeString(mapData->penaltyOnDeath);
                        if (mapData->GetPenaltyTime() > 0)
                        {
                            oss2 << "。当前累计惩罚：";
                            oss2 << secsToTimeString(mapData->GetPenaltyTime());

                            oss << "。当前累计惩罚：";
                            oss << secsToTimeString(mapData->GetPenaltyTime());
                        }
                        else
                            oss2 << "。目前尚无死亡！";
                        MythicPlus::BroadcastToPlayer(player, MythicPlus::Utils::RedColored(oss2.str()));
                    }
                }
                else
                    oss << "已进入一个已完成的史诗钥石副本。";
                MythicPlus::AnnounceToPlayer(player, oss.str());
            }
        }
        else
        {
            // if there is a saved dungeon for this non M+ dungeon (as mythic+), it means the server was restarted and now the dungeon
            // is no longer M+ capable
            if (savedDungeon != nullptr && savedDungeon->isMythic)
            {
                MythicPlus::BroadcastToPlayer(player, "该副本曾保存为史诗钥石，但现在不再支持史诗钥石模式。");
                MythicPlus::FallbackTeleport(player);
                return;
            }
        }
    }

    void OnMapUpdate(Map* map, uint32 diff) override
    {
        if (sMythicPlus->IsMapInMythicPlus(map))
        {
            MythicPlus::MapData* mapData = sMythicPlus->GetMapData(map, false);
            ASSERT(mapData);
                if (mapData->receiveLoot && !mapData->done)
                {
                    if (mapData->updateTimer / 1000 + mapData->GetPenaltyTime() > mapData->timeLimit)
                    {
                        MythicPlus::AnnounceToMap(map, "时间到！将不再获得任何史诗钥石战利品。");
                        mapData->receiveLoot = false;
                    }

                mapData->updateTimer += diff;
            }

            for (auto* affix : mapData->mythicLevel->affixes)
                affix->HandlePeriodicEffectMap(map, diff);
        }
        else
        {
            if (sMythicPlus->CanMapBeMythicPlus(map))
            {
                // check if keystone was used
                MythicPlus::MapData* mapData = sMythicPlus->GetMapData(map, false);
                if (mapData != nullptr && mapData->keystoneTimer > 0 && mapData->mythicPlusStartTimer == 0)
                {
                    uint32 instanceId = map->GetInstanceId();
                    
                    if (instanceTimer[instanceId] > MythicPlus::KEYSTONE_START_TIMER)
                    {
                        const MythicPlus::MythicPlusDungeonInfo* dsave = sMythicPlus->GetSavedDungeonInfo(instanceId);
                        if (dsave != nullptr)
                        {
                            // at this point there shouldn't be any dungeon save available, it pretty much means the dungeon is saved as non M+
                            return;
                        }

                        mapData->mythicPlusStartTimer = MythicPlus::Utils::GameTimeCount();

                        const MythicLevel* mythicLevel = sMythicPlus->GetMythicLevel(mapData->keystoneLevel);
                        ASSERT(mythicLevel);

                        std::ostringstream oss;
                        oss << "史诗钥石计时开始！";
                        oss << " 在此时间内完成即可获得战利品：" << secsToTimeString(mythicLevel->timeLimit) << "。";
                        oss << "祝你玩得开心！";
                        MythicPlus::AnnounceToMap(map, oss.str());

                        uint32 timeLimit = mythicLevel->timeLimit;
                        uint32 mlevel = mythicLevel->level;
                        sMythicPlus->SaveDungeonInfo(instanceId, map->GetId(), timeLimit, mapData->mythicPlusStartTimer, mlevel, sMythicPlus->GetPenaltyOnDeath(), 0, false);

                        mapData->mythicLevel = mythicLevel;
                        mapData->timeLimit = timeLimit;
                        mapData->deaths = 0;
                        mapData->penaltyOnDeath = sMythicPlus->GetPenaltyOnDeath();

                        if (mapData->penaltyOnDeath > 0)
                            sMythicPlus->BroadcastToMap(map, MythicPlus::Utils::RedColored("死亡将带来时间惩罚：" + secsToTimeString(mapData->penaltyOnDeath)));
                    }
                    else
                        instanceTimer[instanceId] += diff;
                }
            }
        }
    }

    void OnDestroyInstance(MapInstanced* /*mapInstanced*/, Map* map) override
    {
        sMythicPlus->RemoveDungeonInfo(map->GetInstanceId());
    }
};

void AddSC_mythic_plus_all_mapscript()
{
    new mythic_plus_all_mapscript();
}
