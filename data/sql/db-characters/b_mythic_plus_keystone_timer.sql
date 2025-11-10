DROP TABLE IF EXISTS `_WY神话_钥石计时`;
CREATE TABLE `_WY神话_钥石计时`(
	`角色ID` int unsigned NOT NULL,
	`购买时间` bigint unsigned NOT NULL,
	PRIMARY KEY (`角色ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
