/*
 * Credits: silviu20092
 */

#include "ScriptMgr.h"
#include "Config.h"
#include "mythic_plus.h"

class mythic_plus_worldscript : public WorldScript
{
public:
    mythic_plus_worldscript() : WorldScript("mythic_plus_worldscript",
        {
            WORLDHOOK_ON_BEFORE_WORLD_INITIALIZED,
            WORLDHOOK_ON_UPDATE,
            WORLDHOOK_ON_AFTER_CONFIG_LOAD
        })
    {
    }

    void OnBeforeWorldInitialized() override
    {
        sMythicPlus->LoadFromDB();
    }

    void OnUpdate(uint32 diff) override
    {
        sMythicPlus->ProcessQueryCallbacks();

        uint32 snapshotsTimer = sMythicPlus->GetMythicSnapshotsTimer();
        if (snapshotsTimer == 0 || snapshotsTimer >= MythicPlus::MYTHIC_SNAPSHOTS_TIMER_FREQ)
        {
            sMythicPlus->LoadMythicPlusSnapshotsFromDB();
            sMythicPlus->ResetMythicSnapshotsTimer();
        }

        sMythicPlus->UpdateMythicSnapshotsTimer(diff);

        // 定期检查并重置过期的史诗钥石等级
        uint32 autoResetTimer = sMythicPlus->GetAutoResetCheckTimer();
        if (autoResetTimer == 0 || autoResetTimer >= MythicPlus::AUTO_RESET_CHECK_TIMER_FREQ)
        {
            sMythicPlus->CheckAndResetExpiredLevels();
            sMythicPlus->ResetAutoResetCheckTimer();
        }

        sMythicPlus->UpdateAutoResetCheckTimer(diff);
    }

    void OnAfterConfigLoad(bool reload) override
    {
        sMythicPlus->ProcessConfig(reload);
    }
};

void AddSC_mythic_plus_worldscript()
{
    new mythic_plus_worldscript();
}
