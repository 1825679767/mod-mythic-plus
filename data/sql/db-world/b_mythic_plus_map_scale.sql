DROP TABLE IF EXISTS `_WY神话_地图缩放`;
CREATE TABLE `_WY神话_地图缩放`(
	`地图ID` smallint unsigned NOT NULL,
	`地图难度` smallint unsigned NOT NULL,
	`小怪伤害系数` float NOT NULL default '1',
	`首领伤害系数` float NOT NULL default '1'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

insert into `_WY神话_地图缩放`(`地图ID`, `地图难度`, `小怪伤害系数`, `首领伤害系数`) values (389, 0, 4, 4.2);
insert into `_WY神话_地图缩放`(`地图ID`, `地图难度`, `小怪伤害系数`, `首领伤害系数`) values (47, 0, 4, 4.2);
