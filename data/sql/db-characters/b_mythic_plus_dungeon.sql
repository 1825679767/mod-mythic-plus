DROP TABLE IF EXISTS `_WY神话_副本信息`;
CREATE TABLE `_WY神话_副本信息`(
	`实例ID` int unsigned NOT NULL,
	`地图ID` smallint unsigned NOT NULL,
	`时间限制` int unsigned NOT NULL,
	`开始时间` bigint unsigned NOT NULL DEFAULT '0',
	`神话等级` smallint unsigned NOT NULL DEFAULT '0',
	`已完成` tinyint unsigned NOT NULL DEFAULT '0',
	`是神话模式` tinyint unsigned NOT NULL DEFAULT '1',
	`死亡惩罚` int unsigned NOT NULL DEFAULT '0',
	`死亡次数` int unsigned NOT NULL DEFAULT '0',
	PRIMARY KEY (`实例ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
