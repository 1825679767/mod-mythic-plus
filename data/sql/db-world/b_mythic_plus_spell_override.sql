DROP TABLE IF EXISTS `_WY神话_法术调整`;
CREATE TABLE `_WY神话_法术调整`(
	`法术ID` int unsigned NOT NULL,
	`地图ID` int unsigned NOT NULL,
	`伤害系数` float default '-1',
	`持续伤害系数` float default '-1',
	`备注` varchar(255),
	PRIMARY KEY (`法术ID`, `地图ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

INSERT INTO `_WY神话_法术调整` (`法术ID`, `地图ID`, `伤害系数`, `持续伤害系数`, `备注`) VALUES (9532,389,3.75, -1,'怒焰萨满 - 闪电箭');
INSERT INTO `_WY神话_法术调整` (`法术ID`, `地图ID`, `伤害系数`, `持续伤害系数`, `备注`) VALUES (11968,389,18,-1,'熔岩元素 - 火焰护盾');
INSERT INTO `_WY神话_法术调整` (`法术ID`, `地图ID`, `伤害系数`, `持续伤害系数`, `备注`) VALUES (18266,389,-1,8,'炽刃教徒 - 痛苦诅咒');
INSERT INTO `_WY神话_法术调整` (`法术ID`, `地图ID`, `伤害系数`, `持续伤害系数`, `备注`) VALUES (20800,389,5,12,'唤焰者杰克索 - 献祭(持续)');
