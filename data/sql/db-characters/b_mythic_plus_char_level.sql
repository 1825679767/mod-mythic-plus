DROP TABLE IF EXISTS `_WY神话_角色等级`;
CREATE TABLE `_WY神话_角色等级`(
	`角色ID` int unsigned NOT NULL,
	`神话等级` int unsigned NOT NULL,
	`上次升级时间` bigint unsigned NOT NULL DEFAULT '0',
	PRIMARY KEY (`角色ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
