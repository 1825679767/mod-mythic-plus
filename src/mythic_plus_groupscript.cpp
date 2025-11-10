/*
 * Credits: silviu20092
 */

#include "ScriptMgr.h"
#include "mythic_plus.h"

class mythic_plus_groupscript : public GroupScript
{
public:
    mythic_plus_groupscript() : GroupScript("mythic_plus_groupscript",
        {
            GROUPHOOK_ON_ADD_MEMBER
        })
    {

    }

    void OnAddMember(Group* group, ObjectGuid guid) override
    {
        ObjectGuid leaderGuid = group->GetLeaderGUID();
        if (sMythicPlus->GetCurrentMythicPlusLevelForGUID(leaderGuid.GetCounter()) && guid != leaderGuid)
        {
            Player* player = ObjectAccessor::FindConnectedPlayer(guid);
            if (player)
            {
                // 只有在可以进行史诗钥石的副本中才提示
                Map* map = player->GetMap();
                if (map && sMythicPlus->CanMapBeMythicPlus(map))
                {
                    std::ostringstream oss;
                    oss << "该队伍的队长已设置史诗钥石层数（层数：";
                    oss << sMythicPlus->GetCurrentMythicPlusLevelForGUID(leaderGuid.GetCounter());
                    oss << ")！队长可以使用史诗钥石将副本转换为史诗钥石副本。";
                    MythicPlus::BroadcastToPlayer(player, oss.str());
                }
            }
        }
    }
};

void AddSC_mythic_plus_groupscript()
{
    new mythic_plus_groupscript();
}
