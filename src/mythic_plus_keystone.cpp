/*
 * Credits: silviu20092
 */

#include "ScriptMgr.h"
#include "mythic_plus.h"
#include <sstream>

class mythic_plus_keystone : public ItemScript
{
public:
    mythic_plus_keystone() : ItemScript("mythic_plus_keystone") {}

    bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override
    {
        Map* map = player->GetMap();
        if (sMythicPlus->CanMapBeMythicPlus(map))
        {
            // only group's leader can use the keystone
            if (!MythicPlus::Utils::IsGroupLeader(player))
                MythicPlus::BroadcastToPlayer(player, "只有队长才能使用史诗钥石。");
            else
            {
                // now check if the group's leader actually has a set m+ level
                if (sMythicPlus->GetCurrentMythicPlusLevel(player) == 0)
                    MythicPlus::BroadcastToPlayer(player, "你尚未选择史诗钥石层数。");
                else
                {
                    MythicPlus::MapData* mapData = sMythicPlus->GetMapData(map);
                    if (mapData->mythicPlusStartTimer > 0)
                        MythicPlus::BroadcastToPlayer(player, "史诗钥石副本已在进行或已完成。");
                    else if (mapData->keystoneTimer > 0)
                        MythicPlus::BroadcastToPlayer(player, "钥石已被使用，正在等待史诗钥石开启…");
                    else
                    {
                        // lets check if a dungeon save was performed, in which case it must be saved as M+
                        const MythicPlus::MythicPlusDungeonInfo* dsave = sMythicPlus->GetSavedDungeonInfo(map->GetInstanceId());
                        if (dsave != nullptr && !dsave->isMythic)
                            MythicPlus::BroadcastToPlayer(player, "该副本已标记为非史诗钥石，无法再使用钥石。");
                        else
                        {
                            if (player->IsInCombat())
                                MythicPlus::BroadcastToPlayer(player, "战斗中无法使用史诗钥石。");
                            else
                            {
                                // every player in the group must be online and at max level
                                if (!sMythicPlus->CheckGroupLevelForKeystone(player))
                                {
                                    // 生成动态错误消息
                                    std::ostringstream errMsg;
                                    errMsg << "队伍限制：";

                                    bool needAnd = false;
                                    if (sMythicPlus->GetCheckGroupOnline())
                                    {
                                        errMsg << "所有玩家必须在线";
                                        needAnd = true;
                                    }

                                    if (sMythicPlus->GetRequiredPlayerLevel() > 1)
                                    {
                                        if (needAnd)
                                            errMsg << "且";
                                        errMsg << "等级需达到 " << sMythicPlus->GetRequiredPlayerLevel() << " 级";
                                    }

                                    MythicPlus::BroadcastToPlayer(player, errMsg.str());
                                }
                                else
                                {
                                    mapData->keystoneTimer = MythicPlus::Utils::GameTimeCount();
                                    mapData->keystoneLevel = sMythicPlus->GetCurrentMythicPlusLevel(player);
                                    std::ostringstream oss;
                                    oss << "史诗钥石将在 ";
                                    oss << secsToTimeString(MythicPlus::KEYSTONE_START_TIMER / 1000);
                                    oss << " 后开始。设置的层数：";
                                    oss << Acore::ToString(mapData->keystoneLevel);
                                    MythicPlus::AnnounceToGroup(player, oss.str());

                                    sMythicPlus->RemoveKeystone(player);
                                }
                            }
                        }
                    }
                }
            }
        }
        else
            MythicPlus::BroadcastToPlayer(player, "必须在可进行史诗钥石的副本中才能使用钥石。");
        return true;
    }
};

void AddSC_mythic_plus_keystone()
{
    new mythic_plus_keystone();
}
