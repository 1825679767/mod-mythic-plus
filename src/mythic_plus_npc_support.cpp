/*
 * Credits: silviu20092
 */

#include "Player.h"
#include "Creature.h"
#include "ScriptedGossip.h"
#include "StringConvert.h"
#include "Group.h"
#include "mythic_plus.h"
#include "mythic_affix.h"
#include "mythic_plus_npc_support.h"

void MythicPlusNpcSupport::AddMainMenu(Player* player, Creature* creature)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.backMenu = false;
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_MYTHIC_NPC_MENU;

    if (!sMythicPlus->IsEnabled())
    {
        Identifier* disabledIdnt = new Identifier();
        disabledIdnt->id = 0;
        disabledIdnt->uiName = MythicPlus::Utils::RedColored("!!! 系统未启用 !!!");
        pagedData.data.push_back(disabledIdnt);
    }

    // 显示当前等级
    uint32 setLevel = sMythicPlus->GetCurrentMythicPlusLevel(player);
    Identifier* levelIdnt = new Identifier();
    levelIdnt->id = 1;
    levelIdnt->optionIcon = GOSSIP_ICON_BATTLE;
    std::ostringstream oss;
    oss << "当前史诗钥石等级：" << MythicPlus::Utils::Colored(Acore::ToString(setLevel), "0a4a0e") << " 级";
    levelIdnt->uiName = oss.str();
    pagedData.data.push_back(levelIdnt);

    // 重置等级选项（始终显示）
    Identifier* resetIdnt = new Identifier();
    resetIdnt->id = 2;
    resetIdnt->uiName = MythicPlus::Utils::Colored("重置史诗钥石等级为 1 级", "b50505");
    resetIdnt->optionIcon = GOSSIP_ICON_BATTLE;
    pagedData.data.push_back(resetIdnt);

    if (player->GetGroup() != nullptr)
    {
        ObjectGuid leaderGuid = player->GetGroup()->GetLeaderGUID();
        uint32 leaderLevel = sMythicPlus->GetCurrentMythicPlusLevelForGUID(leaderGuid.GetCounter());
        Player* leader = ObjectAccessor::FindConnectedPlayer(leaderGuid);
        Identifier* dungeonLevelIdnt = new Identifier();
        dungeonLevelIdnt->id = 3;
        dungeonLevelIdnt->optionIcon = GOSSIP_ICON_CHAT;
        std::ostringstream goss;
        goss << "当前副本的史诗钥石等级（基于队长）：";
        if (leaderLevel == 0)
            goss << MythicPlus::Utils::Colored("无（0）", "b50505");
        else
            goss << leaderLevel;
        if (!leader)
            goss << " [队长离线]";
        dungeonLevelIdnt->uiName = goss.str();
        pagedData.data.push_back(dungeonLevelIdnt);
    }

    Identifier* mPlusListIdnt = new Identifier();
    mPlusListIdnt->id = 4;
    mPlusListIdnt->uiName = "所有可进行史诗钥石的副本列表";
    pagedData.data.push_back(mPlusListIdnt);

    Identifier* standingsRefreshIdnt = new Identifier();
    standingsRefreshIdnt->id = 5;
    std::ostringstream toss;
    toss << "距离史诗钥石排行榜刷新还有：";
    toss << MythicPlus::Utils::Colored(secsToTimeString((MythicPlus::MYTHIC_SNAPSHOTS_TIMER_FREQ - sMythicPlus->GetMythicSnapshotsTimer()) / 1000), "b50505");
    standingsRefreshIdnt->uiName = toss.str();
    pagedData.data.push_back(standingsRefreshIdnt);

    Identifier* standings = new Identifier();
    standings->id = 6;
    standings->uiName = "史诗钥石排行榜 -->";
    pagedData.data.push_back(standings);

    Identifier* keystoneIdnt = new Identifier();
    keystoneIdnt->id = 7;
    std::ostringstream koss;
    koss << MythicPlus::Utils::Colored("获取史诗钥石", "700c63");
    if (sMythicPlus->GetKeystoneBuyTimer() > 0)
    {
        uint32 playerKeystoneBuyTimer = sMythicPlus->GetKeystoneBuyTimer(player);
        std::string available = MythicPlus::Utils::GreenColored(" [可立即领取]");
        if (playerKeystoneBuyTimer > 0)
        {
            uint64 now = MythicPlus::Utils::GameTimeCount();
            uint64 diff = now - playerKeystoneBuyTimer;
            if (diff < sMythicPlus->GetKeystoneBuyTimer() * 60)
                available = MythicPlus::Utils::RedColored(" [还需 " + secsToTimeString(sMythicPlus->GetKeystoneBuyTimer() * 60 - diff) + " 才可领取]");
        }
        koss << available;
    }
    keystoneIdnt->uiName = koss.str();
    keystoneIdnt->optionIcon = GOSSIP_ICON_MONEY_BAG;
    pagedData.data.push_back(keystoneIdnt);

    Identifier* randomMythicIdnt = new Identifier();
    randomMythicIdnt->id = 8;
    randomMythicIdnt->uiName = "查看可能出现的随机词缀 -->";
    randomMythicIdnt->optionIcon = GOSSIP_ICON_BATTLE;
    pagedData.data.push_back(randomMythicIdnt);

    Identifier* bye = new Identifier();
    bye->id = 9;
    bye->uiName = "不用了……";
    pagedData.data.push_back(bye);

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

void MythicPlusNpcSupport::AddMythicPlusLevels(Player* player, Creature* creature)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_MYTHIC_LEVELS;

    const MythicLevelContainer& mythicLevels = sMythicPlus->GetAllMythicLevels();
    for (const auto& mlevel : mythicLevels)
    {
        Identifier* idnt = new Identifier();
        idnt->id = mlevel.level;
        idnt->optionIcon = GOSSIP_ICON_BATTLE;
        std::ostringstream oss;
        oss << "钥石层数 " << mlevel.level;
        oss << "（" << mlevel.affixes.size() << " 个词缀）";
        if (mlevel.randomAffixCount > 0)
            oss << "（" << mlevel.randomAffixCount << " 个随机词缀）";
        oss << " -->";
        idnt->uiName = oss.str();
        pagedData.data.push_back(idnt);
    }

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

void MythicPlusNpcSupport::AddMythicPlusLevelInfo(Player* player, Creature* creature, uint32 mythicLevel)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_MYTHIC_LEVEL_INFO;
    pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->mythicLevel = mythicLevel;

    uint32 id = 0;

    // 禁用手动设置等级功能，只允许通过完成副本升级
    // 改为显示等级信息（只读）
    Identifier* idnt = new Identifier();
    idnt->id = ++id;
    idnt->optionIcon = GOSSIP_ICON_CHAT;
    idnt->uiName = MythicPlus::Utils::Colored("史诗钥石层数 " + Acore::ToString(mythicLevel) + " 的详细信息", "0a4a0e");
    pagedData.data.push_back(idnt);

    const MythicLevel* level = sMythicPlus->GetMythicLevel(mythicLevel);
    ASSERT(level);

    Identifier* timerIdnt = new Identifier();
    timerIdnt->id = ++id;
    timerIdnt->uiName = "获取奖励的时限：" + secsToTimeString(level->timeLimit);
    pagedData.data.push_back(timerIdnt);

    for (int i = 0; i < level->affixes.size(); i++)
    {
        const MythicAffix* affix = level->affixes.at(i);

        Identifier* affixIdnt = new Identifier();
        affixIdnt->id = ++id;
        std::ostringstream oss;
        oss << "词缀 ";
        oss << i + 1 << "：";
        oss << affix->ToString();
        if (affix->IsRandom())
            oss << MythicPlus::Utils::Colored(" [随机生成]", "1a0966");
        affixIdnt->uiName = oss.str();
        pagedData.data.push_back(affixIdnt);
    }

    Identifier* rewardsIdnt = new Identifier();
    rewardsIdnt->id = ++id;
    rewardsIdnt->optionIcon = GOSSIP_ICON_MONEY_BAG;
    rewardsIdnt->uiName = MythicPlus::Utils::Colored("-- 奖励 --", "0d852d");
    pagedData.data.push_back(rewardsIdnt);

    const MythicReward& reward = level->reward;
    if (reward.money)
    {
        Identifier* moneyIdnt = new Identifier();
        moneyIdnt->id = ++id;
        moneyIdnt->optionIcon = GOSSIP_ICON_MONEY_BAG;
        moneyIdnt->uiName = "金币：" + MythicPlus::Utils::CopperToMoneyStr(reward.money, false);
        pagedData.data.push_back(moneyIdnt);
    }

    if (!reward.tokens.empty())
    {
        for (const auto& token : reward.tokens)
        {
            Identifier* tokenIdnt = new Identifier();
            tokenIdnt->id = ++id;
            tokenIdnt->optionIcon = GOSSIP_ICON_VENDOR;
            std::ostringstream oss;
            oss << MythicPlus::Utils::ItemLinkForUI(token.first, player);
            oss << " - " << token.second << "×";
            tokenIdnt->uiName = oss.str();
            pagedData.data.push_back(tokenIdnt);
        }
    }

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

void MythicPlusNpcSupport::AddMythicPlusDungeonList(Player* player, Creature* creature)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_LIST;

    const std::unordered_map<uint32, MythicPlus::MythicPlusCapableDungeon>& dungeons = sMythicPlus->GetAllMythicPlusDungeons();
    LocaleConstant locale = player->GetSession()->GetSessionDbcLocale();
    uint32 id = 0;
    for (const auto& dpair : dungeons)
    {
        uint32 mapEntry = dpair.first;
        Difficulty diff = dpair.second.minDifficulty;
        std::string dungeonName = dpair.second.dungeonName;

        Identifier* idnt = new Identifier();
        idnt->id = ++id;
        std::ostringstream oss;

        // 优先使用自定义副本名称，如果为空则使用 DBC 名称
        if (!dungeonName.empty())
        {
            oss << dungeonName;
        }
        else
        {
            MapEntry const* map = sMapStore.LookupEntry(mapEntry);
            if (map)
                oss << map->name[locale];
            else
                oss << "未知副本";
        }

        oss << " [";
        if (diff == DUNGEON_DIFFICULTY_NORMAL)
        {
            if (MythicPlus::Utils::CanBeHeroic(mapEntry))
                oss << "普通/英雄]";
            else
                oss << "普通]";
        }
        else
            oss << "仅限英雄]";
        idnt->uiName = oss.str();
        pagedData.data.push_back(idnt);
    }

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

void MythicPlusNpcSupport::AddMythicPlusDungeonListForSnapshots(Player* player, Creature* creature, uint32 snapMythicLevel)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_LIST_SNAPSHOT;
    pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->snapMythicLevel = snapMythicLevel;

    Identifier* mlevelIdnt = new Identifier();
    mlevelIdnt->id = 1;
    std::ostringstream oss;
    oss << "已选择的史诗钥石等级：";
    if (snapMythicLevel == 0)
        oss << "全部";
    else
        oss << snapMythicLevel;
    mlevelIdnt->uiName = oss.str();
    mlevelIdnt->optionIcon = GOSSIP_ICON_CHAT;
    pagedData.data.push_back(mlevelIdnt);

    const std::unordered_map<uint32, MythicPlus::MythicPlusCapableDungeon>& dungeons = sMythicPlus->GetAllMythicPlusDungeons();
    LocaleConstant locale = player->GetSession()->GetSessionDbcLocale();
    for (const auto& dpair : dungeons)
    {
        uint32 mapEntry = dpair.first;
        std::string dungeonName = dpair.second.dungeonName;

        const std::vector<std::pair<std::pair<uint32, uint64>, std::vector<MythicPlus::MythicPlusDungeonSnapshot>>> snapshots = sMythicPlus->GetMapSnapshot(mapEntry, snapMythicLevel);

        Identifier* idnt = new Identifier();
        idnt->id = mapEntry;
        std::ostringstream oss;

        // 优先使用自定义副本名称，如果为空则使用 DBC 名称
        if (!dungeonName.empty())
        {
            oss << dungeonName;
        }
        else
        {
            MapEntry const* map = sMapStore.LookupEntry(mapEntry);
            if (map)
                oss << map->name[locale];
            else
                oss << "未知副本";
        }

        oss << " [总场次：";
        if (snapshots.empty())
            oss << MythicPlus::Utils::Colored("无", "b50505");
        else
            oss << snapshots.size();
        oss << "]";
        idnt->uiName = oss.str();
        pagedData.data.push_back(idnt);
    }

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

void MythicPlusNpcSupport::AddMythicPlusSnapshotAllRuns(Player* player, Creature* creature, uint32 mapEntry)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_LIST_SNAPSHOT_RUNS;
    pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->mapEntry = mapEntry;

    const std::unordered_map<uint32, MythicPlus::MythicPlusCapableDungeon>& dungeons = sMythicPlus->GetAllMythicPlusDungeons();
    LocaleConstant locale = player->GetSession()->GetSessionDbcLocale();
    std::string dungeonName;

    // 尝试获取自定义副本名称
    if (dungeons.find(mapEntry) != dungeons.end())
    {
        dungeonName = dungeons.at(mapEntry).dungeonName;
    }

    // 如果没有自定义名称，使用 DBC 名称
    if (dungeonName.empty())
    {
        MapEntry const* map = sMapStore.LookupEntry(mapEntry);
        if (map)
            dungeonName = map->name[locale];
        else
            dungeonName = "未知副本";
    }

    Identifier* mapIdnt = new Identifier();
    mapIdnt->id = 1;
    std::ostringstream oss;
    oss << "史诗钥石最佳计时：";
    oss << dungeonName;
    mapIdnt->uiName = oss.str();
    pagedData.data.push_back(mapIdnt);

    uint32 snapMythicLevel = pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->snapMythicLevel;

    const std::vector<std::pair<std::pair<uint32, uint64>, std::vector<MythicPlus::MythicPlusDungeonSnapshot>>> snapshots = sMythicPlus->GetMapSnapshot(mapEntry, snapMythicLevel);
    if (!snapshots.empty())
    {
        uint32 id = 1;
        for (const auto& s : snapshots)
        {
            const MythicPlus::MythicPlusDungeonSnapshot& snap = s.second.at(0);
            uint32 internalId = snap.internalId;

            Identifier* idnt = new Identifier();
            idnt->id = internalId + 10;
            std::ostringstream oss;
            oss << id++ << ". ";
            if (snap.totalTime > 0)
            {
                oss << secsToTimeString(snap.totalTime);
                oss << " [限定时间：";
                oss << secsToTimeString(snap.timelimit);
                oss << "]";
                if (snap.rewarded)
                    oss << MythicPlus::Utils::GreenColored(" [已获取奖励]");
                else
                    oss << MythicPlus::Utils::RedColored(" [未获奖励]");
            }
            else
            {
                oss << MythicPlus::Utils::RedColored("未完成");
                oss << " [限定时间：";
                oss << secsToTimeString(snap.timelimit);
                oss << "]";
            }
            oss << " [M+ 等级 ";
            oss << snap.mythicLevel;
            oss << "]";
            if (snap.difficulty == DUNGEON_DIFFICULTY_NORMAL)
                oss << " [普通模式]";
            else
                oss << MythicPlus::Utils::Colored(" [英雄模式]", "9e1849");
            idnt->uiName = oss.str();
            pagedData.data.push_back(idnt);
        }
    }

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

void MythicPlusNpcSupport::AddMythicPlusAllLevels(Player* player, Creature* creature)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_MYTHIC_ALL_LEVELS;

    Identifier* allIdnt = new Identifier();
    allIdnt->id = 0;
    allIdnt->uiName = "所有史诗钥石等级";
    pagedData.data.push_back(allIdnt);

    const MythicLevelContainer& mythicLevels = sMythicPlus->GetAllMythicLevels();
    for (const auto& mlevel : mythicLevels)
    {
        Identifier* idnt = new Identifier();
        idnt->id = mlevel.level;
        idnt->optionIcon = GOSSIP_ICON_BATTLE;
        std::ostringstream oss;
        oss << "钥石层数 " << mlevel.level << " -- >";
        idnt->uiName = oss.str();
        pagedData.data.push_back(idnt);
    }

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

void MythicPlusNpcSupport::AddMythicPlusDungeonSnapshotDetails(Player* player, Creature* creature, uint32 internalId)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_SNAPSHOT_DETAILS;
    pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->internalId = internalId;

    uint32 mapEntry = pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->mapEntry;
    uint32 snapMythicLevel = pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->snapMythicLevel;
    const std::vector<std::pair<std::pair<uint32, uint64>, std::vector<MythicPlus::MythicPlusDungeonSnapshot>>> snapshots = sMythicPlus->GetMapSnapshot(mapEntry, snapMythicLevel);

    std::vector<MythicPlus::MythicPlusDungeonSnapshot> chosenSnaps;
    for (const auto& s : snapshots)
    {
        if (s.second.at(0).internalId == internalId)
        {
            chosenSnaps = s.second;
            break;
        }
    }
    if (chosenSnaps.empty())
        return;

    std::sort(chosenSnaps.begin(), chosenSnaps.end(), [](const MythicPlus::MythicPlusDungeonSnapshot& a, const MythicPlus::MythicPlusDungeonSnapshot& b) {
        return a.snapTime < b.snapTime;
    });

    const std::unordered_map<uint32, MythicPlus::MythicPlusCapableDungeon>& dungeons = sMythicPlus->GetAllMythicPlusDungeons();
    LocaleConstant locale = player->GetSession()->GetSessionDbcLocale();
    std::string dungeonName;

    // 尝试获取自定义副本名称
    if (dungeons.find(mapEntry) != dungeons.end())
    {
        dungeonName = dungeons.at(mapEntry).dungeonName;
    }

    // 如果没有自定义名称，使用 DBC 名称
    if (dungeonName.empty())
    {
        MapEntry const* map = sMapStore.LookupEntry(mapEntry);
        if (map)
            dungeonName = map->name[locale];
        else
            dungeonName = "未知副本";
    }

    const MythicPlus::MythicPlusDungeonSnapshot* csnap = &chosenSnaps.at(0);

    Identifier* idnt = new Identifier();
    idnt->id = 1;
    std::ostringstream oss;
    oss << "史诗钥石副本：";
    oss << dungeonName;
    oss << " ，层数：";
    oss << csnap->mythicLevel;
    idnt->uiName = oss.str();
    pagedData.data.push_back(idnt);

    oss.str("");
    oss.clear();

    Identifier* startTimeIdnt = new Identifier();
    startTimeIdnt->id = 2;
    oss << "开始时间：";
    oss << MythicPlus::Utils::DateFromSeconds(csnap->startTime);
    oss << " [UTC 时间]";
    startTimeIdnt->uiName = oss.str();
    pagedData.data.push_back(startTimeIdnt);

    oss.str("");
    oss.clear();

    Identifier* endTimeIdnt = new Identifier();
    endTimeIdnt->id = 3;
    if (csnap->totalTime > 0)
    {
        oss << "结束时间：";
        oss << MythicPlus::Utils::DateFromSeconds(csnap->endTime);
        oss << " [UTC 时间]";
        oss << " [耗时：";
        oss << secsToTimeString(csnap->totalTime);
        oss << "]";
    }
    else
        oss << MythicPlus::Utils::RedColored("副本尚未结束（或实例已失效）");
    endTimeIdnt->uiName = oss.str();
    pagedData.data.push_back(endTimeIdnt);

    Identifier* deathsIdnt = new Identifier();
    deathsIdnt->id = 4;
    oss.str("");
    oss.clear();
    if (csnap->totalDeaths > 0)
    {
        oss << "死亡次数：";
        oss << MythicPlus::Utils::RedColored(Acore::ToString(csnap->totalDeaths));
        oss << "。时间惩罚：";
        oss << secsToTimeString(csnap->penaltyOnDeath * csnap->totalDeaths);
    }
    else
        oss << MythicPlus::Utils::GreenColored("无死亡");
    deathsIdnt->uiName = oss.str();
    pagedData.data.push_back(deathsIdnt);

    uint32 id = 4;
    for (const auto& s : chosenSnaps)
    {
        oss.str("");
        oss.clear();

        oss << MythicPlus::Utils::Colored(MythicPlus::Utils::GetCreatureNameByEntry(player, s.entry), "102163");
        oss << " 击败于：";
        oss << MythicPlus::Utils::DateFromSeconds(s.snapTime);
        oss << " [战斗耗时 ";
        oss << secsToTimeString(s.combatTime);
        oss << "]";
        oss << " [玩家：";
        oss << MythicPlus::Utils::Colored(s.players, "6e1849");
        oss << "]";

        if (s.randomAffixCount > 0)
            oss << " [随机词缀：" << s.randomAffixCount << "]";

        Identifier* idnt = new Identifier();
        idnt->id = ++id;
        idnt->uiName = oss.str();
        pagedData.data.push_back(idnt);
    }

    if (csnap->totalTime > 0)
    {
        Identifier* rewardIdnt = new Identifier();
        rewardIdnt->id = ++id;
        if (csnap->rewarded)
            rewardIdnt->uiName = MythicPlus::Utils::GreenColored("战胜计时——奖励已发放");
        else
            rewardIdnt->uiName = MythicPlus::Utils::RedColored("未获奖励——超出计时限制");
        pagedData.data.push_back(rewardIdnt);
    }

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

void MythicPlusNpcSupport::AddRandomAfixes(Player* player, Creature* creature)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_RANDOM_AFFIXES;

    uint32 id = 1;

    Identifier* infoIdnt = new Identifier();
    infoIdnt->id = id++;
    infoIdnt->uiName = "部分钥石层数会从该列表中抽取固定数量的随机词缀，服务器重启时会重新洗牌。";
    infoIdnt->optionIcon = GOSSIP_ICON_CHAT;
    pagedData.data.push_back(infoIdnt);

    const MythicLevelContainer& mythicLevels = sMythicPlus->GetAllMythicLevels();
    for (const auto& mlevel : mythicLevels)
    {
        if (mlevel.randomAffixCount > 0)
        {
            Identifier* idnt = new Identifier();
            idnt->id = 100 + mlevel.level;
            std::ostringstream oss;
            oss << "钥石层数 ";
            oss << mlevel.level;
            oss << " 拥有 ";
            oss << mlevel.randomAffixCount << " 个随机词缀 -->";
            idnt->uiName = oss.str();
            pagedData.data.push_back(idnt);
        }
    }

    Identifier* affixesInfoIdnt = new Identifier();
    affixesInfoIdnt->id = 1000 + (id++);
    affixesInfoIdnt->uiName = "随机词缀池：";
    affixesInfoIdnt->optionIcon = GOSSIP_ICON_CHAT;
    pagedData.data.push_back(affixesInfoIdnt);

    for (uint32 i = 0; i < MythicAffix::RANDOM_AFFIX_MAX_COUNT; i++)
    {
        MythicAffix* affix = MythicAffix::AffixFactory((MythicAffixType)MythicAffix::RandomAffixes[i]);
        ASSERT(affix && affix->IsRandom());

        Identifier* affixIdnt = new Identifier();
        affixIdnt->id = 1000 + (id++);
        std::ostringstream aoss;
        aoss << (i + 1) << ". ";
        aoss << MythicPlus::Utils::Colored(affix->ToString(), "1a0966");
        affixIdnt->uiName = aoss.str();
        pagedData.data.push_back(affixIdnt);

        delete affix;
    }

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

void MythicPlusNpcSupport::AddRandomAffixesForLevel(Player* player, Creature* creature, uint32 level)
{
    PagedData& pagedData = GetPagedData(player);
    pagedData.Reset();
    pagedData.type = GossipSupport::PAGED_DATA_TYPE_RANDOM_AFFIXES_FOR_LEVEL;
    pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->randomMythicLevel = level;

    uint32 id = 1;
    Identifier* levelIdnt = new Identifier();
    levelIdnt->id = id++;
    levelIdnt->uiName = "史诗钥石第 " + Acore::ToString(level) + " 层的随机词缀";
    levelIdnt->optionIcon = GOSSIP_ICON_CHAT;
    pagedData.data.push_back(levelIdnt);

    const MythicLevel* mythicLevel = sMythicPlus->GetMythicLevel(level);
    ASSERT(mythicLevel);

    uint32 affixIndex = 1;
    for (const auto* a : mythicLevel->affixes)
    {
        if (a->IsRandom())
        {
            Identifier* affixIdnt = new Identifier();
            affixIdnt->id = id++;
            std::ostringstream aoss;
            aoss << affixIndex++ << ". ";
            aoss << MythicPlus::Utils::Colored(a->ToString(), "1a0966");
            affixIdnt->uiName = aoss.str();
            pagedData.data.push_back(affixIdnt);
        }
    }

    pagedData.SortAndCalculateTotals(CompareIdentifierById);
}

bool MythicPlusNpcSupport::TakePagedDataAction(Player* player, Creature* creature, uint32 action)
{
    PagedData& pagedData = GetPagedData(player);
    if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_NPC_MENU)
    {
        if (action == 1 || action == 0)
        {
            // 显示当前等级，不做操作，只刷新菜单
            return OnGossipHello(player, creature);
        }
        else if (action == 2)
        {
            // 重置等级为1
            if (sMythicPlus->ResetMythicLevel(player))
            {
                CloseGossipMenuFor(player);
                return true;
            }
            else
            {
                MythicPlus::BroadcastToPlayer(player, "重置失败。");
                CloseGossipMenuFor(player);
                return true;
            }
        }
        else if (action == 3 || action == 5)
            return OnGossipHello(player, creature);
        else if (action == 4)
        {
            AddMythicPlusDungeonList(player, creature);
            return AddPagedData(player, creature, 0);
        }
        else if (action == 6)
        {
            AddMythicPlusAllLevels(player, creature);
            return AddPagedData(player, creature, 0);
        }
        else if (action == 7)
        {
            if (sMythicPlus->GiveKeystone(player))
            {
                CloseGossipMenuFor(player);
                return true;
            }
            else
                return OnGossipHello(player, creature);
        }
        else if (action == 8)
        {
            AddRandomAfixes(player, creature);
            return AddPagedData(player, creature, 0);
        }
        else if (action == 9)
        {
            CloseGossipMenuFor(player);
            return true;
        }
    }
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_LEVELS)
    {
        AddMythicPlusLevelInfo(player, creature, action);
        return AddPagedData(player, creature, 0);
    }
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_LEVEL_INFO)
    {
        uint32 chosenMythicLevel = pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->mythicLevel;

        // 禁用手动设置等级功能，只显示等级信息
        // 玩家只能通过完成副本来升级
        if (action == 1)
        {
            // 点击等级信息标题时，提示玩家只能通过完成副本升级
            MythicPlus::BroadcastToPlayer(player, "史诗钥石等级只能通过完成副本挑战来提升，无法手动设置。");
            return AddPagedData(player, creature, 0);
        }
        else
        {
            AddMythicPlusLevelInfo(player, creature, chosenMythicLevel);
            return AddPagedData(player, creature, pagedData.currentPage);
        }
    }
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_LIST)
    {
        AddMythicPlusDungeonList(player, creature);
        return AddPagedData(player, creature, pagedData.currentPage);
    }
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_LIST_SNAPSHOT)
    {
        if (action == 1)
        {
            AddMythicPlusDungeonListForSnapshots(player, creature, pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->snapMythicLevel);
            return AddPagedData(player, creature, pagedData.currentPage);
        }
        AddMythicPlusSnapshotAllRuns(player, creature, action);
        return AddPagedData(player, creature, 0);
    }
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_ALL_LEVELS)
    {
        AddMythicPlusDungeonListForSnapshots(player, creature, action);
        return AddPagedData(player, creature, 0);
    }
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_LIST_SNAPSHOT_RUNS)
    {
        if (action == 1)
        {
            AddMythicPlusSnapshotAllRuns(player, creature, pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->mapEntry);
            return AddPagedData(player, creature, pagedData.currentPage);
        }
        else
        {
            AddMythicPlusDungeonSnapshotDetails(player, creature, action - 10);
            return AddPagedData(player, creature, 0);
        }
    }
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_SNAPSHOT_DETAILS)
    {
        AddMythicPlusDungeonSnapshotDetails(player, creature, pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->internalId);
        return AddPagedData(player, creature, pagedData.currentPage);
    }
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_RANDOM_AFFIXES)
    {
        if (action >= 100 && action <= 1000)
        {
            uint32 level = action - 100;
            AddRandomAffixesForLevel(player, creature, level);
            return AddPagedData(player, creature, 0);
        }
        else
        {
            AddRandomAfixes(player, creature);
            return AddPagedData(player, creature, pagedData.currentPage);
        }
    }
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_RANDOM_AFFIXES_FOR_LEVEL)
    {
        AddRandomAffixesForLevel(player, creature, pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->randomMythicLevel);
        return AddPagedData(player, creature, pagedData.currentPage);
    }

    return GossipSupport::TakePagedDataAction(player, creature, action);
}

/*static*/ bool MythicPlusNpcSupport::CompareIdentifierById(const Identifier* a, const Identifier* b)
{
    return a->id < b->id;
}

uint32 MythicPlusNpcSupport::_PageZeroSender(const PagedData& pagedData) const
{
    if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_LEVELS
        || pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_LIST
        || pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_ALL_LEVELS
        || pagedData.type == GossipSupport::PAGED_DATA_TYPE_RANDOM_AFFIXES)
        return GOSSIP_SENDER_MAIN;
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_LEVEL_INFO)
        return GOSSIP_SENDER_MAIN + 9;
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_LIST_SNAPSHOT)
        return GOSSIP_SENDER_MAIN + 10;
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_LIST_SNAPSHOT_RUNS)
        return GOSSIP_SENDER_MAIN + 11;
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_MYTHIC_DUNGEON_SNAPSHOT_DETAILS)
        return GOSSIP_SENDER_MAIN + 12;
    else if (pagedData.type == GossipSupport::PAGED_DATA_TYPE_RANDOM_AFFIXES_FOR_LEVEL)
        return GOSSIP_SENDER_MAIN + 13;

    return GOSSIP_SENDER_MAIN;
}

bool MythicPlusNpcSupport::OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    PagedData& pagedData = GetPagedData(player);
    if (sender <= GOSSIP_SENDER_MAIN + 2)
        return GossipSupport::OnGossipSelect(player, creature, sender, action);
    else if (sender == GOSSIP_SENDER_MAIN + 9)
    {
        AddMythicPlusLevels(player, creature);
        return AddPagedData(player, creature, 0);
    }
    else if (sender == GOSSIP_SENDER_MAIN + 10)
    {
        AddMythicPlusAllLevels(player, creature);
        return AddPagedData(player, creature, 0);
    }
    else if (sender == GOSSIP_SENDER_MAIN + 11)
    {
        AddMythicPlusDungeonListForSnapshots(player, creature, pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->snapMythicLevel);
        return AddPagedData(player, creature, 0);
    }
    else if (sender == GOSSIP_SENDER_MAIN + 12)
    {
        AddMythicPlusSnapshotAllRuns(player, creature, pagedData.GetCustomInfo<MythicPlusNpcPageInfo>()->mapEntry);
        return AddPagedData(player, creature, 0);
    }
    else if (sender == GOSSIP_SENDER_MAIN + 13)
    {
        AddRandomAfixes(player, creature);
        return AddPagedData(player, creature, 0);
    }

    return false;
}
