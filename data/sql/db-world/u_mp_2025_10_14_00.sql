-- 添加 dungeon_name 字段用于自定义副本名称
ALTER TABLE `mythic_plus_capable_dungeon` ADD COLUMN `dungeon_name` VARCHAR(255) NOT NULL DEFAULT '' AFTER `final_boss_entry`;

-- 更新现有副本的中文名称
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '冠军的试炼' WHERE `map` = 658;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '灵魂洪炉' WHERE `map` = 632;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '安卡赫特：古代王国' WHERE `map` = 619;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '乌特加德之巅' WHERE `map` = 601;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '达克萨隆要塞' WHERE `map` = 600;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '古达克' WHERE `map` = 604;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '艾卓-尼鲁布' WHERE `map` = 602;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '闪电大厅' WHERE `map` = 599;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '岩石大厅' WHERE `map` = 576;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '魔枢' WHERE `map` = 578;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '乌特加德城堡' WHERE `map` = 574;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '紫罗兰监狱' WHERE `map` = 575;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '拉泽芬深堡' WHERE `map` = 389;
UPDATE `mythic_plus_capable_dungeon` SET `dungeon_name` = '剃刀沼泽' WHERE `map` = 47;
