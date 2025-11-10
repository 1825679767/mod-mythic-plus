DROP TABLE IF EXISTS `_WY神话_可用副本`;
CREATE TABLE `_WY神话_可用副本`(
	`地图ID` smallint unsigned NOT NULL,
	`地图难度` smallint unsigned NOT NULL,
	`最终首领ID` int unsigned NOT NULL,
	`副本名称` VARCHAR(255) NOT NULL DEFAULT '',
	PRIMARY KEY (`地图ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (658, 0, 36658, '冠军的试炼');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (632, 0, 36502, '灵魂洪炉');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (619, 0, 29311, '安卡赫特：古代王国');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (601, 0, 29120, '乌特加德之巅');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (600, 0, 26632, '达克萨隆要塞');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (604, 0, 29306, '古达克');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (602, 0, 28923, '艾卓-尼鲁布');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (599, 0, 27978, '闪电大厅');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (576, 0, 26723, '岩石大厅');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (578, 0, 27656, '魔枢');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (574, 0, 23954, '乌特加德城堡');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (575, 0, 26861, '紫罗兰监狱');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (389, 0, 11519, '拉泽芬深堡');
INSERT INTO `_WY神话_可用副本` (`地图ID`, `地图难度`, `最终首领ID`, `副本名称`) VALUES (47, 0, 4421, '剃刀沼泽');
