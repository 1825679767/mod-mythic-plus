-- 存储全局重置时间的表
DROP TABLE IF EXISTS `_WY神话_全局重置`;
CREATE TABLE `_WY神话_全局重置`(
	`记录ID` int unsigned NOT NULL DEFAULT 1,
	`上次重置时间` BIGINT UNSIGNED NOT NULL DEFAULT 0,
	PRIMARY KEY (`记录ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- 初始化记录（使用当前时间）
INSERT INTO `_WY神话_全局重置` (`记录ID`, `上次重置时间`) VALUES (1, UNIX_TIMESTAMP());
