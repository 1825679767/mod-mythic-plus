DROP TABLE IF EXISTS `_WY神话_副本快照`;
CREATE TABLE `_WY神话_副本快照`(
	`实例ID` int unsigned NOT NULL,
	`地图ID` smallint unsigned NOT NULL,
	`地图难度` smallint unsigned NOT NULL,
	`开始时间` bigint unsigned NOT NULL,
	`快照时间` bigint unsigned NOT NULL,
	`战斗时间` int unsigned NOT NULL,
	`时间限制` int unsigned NOT NULL,
	`角色ID` int unsigned NOT NULL,
	`角色名称` varchar(12) NOT NULL,
	`神话等级` smallint unsigned NOT NULL,
	`生物ID` int unsigned NOT NULL,
	`是最终首领` tinyint unsigned NOT NULL DEFAULT '0',
	`已奖励` tinyint unsigned NOT NULL DEFAULT '0',
	`死亡惩罚` int unsigned NOT NULL DEFAULT '0',
	`死亡次数` int unsigned NOT NULL DEFAULT '0',
	`随机词缀数量` int unsigned DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
