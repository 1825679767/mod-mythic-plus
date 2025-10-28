-- 存储全局重置时间的表
DROP TABLE IF EXISTS `mythic_plus_global_reset`;
CREATE TABLE `mythic_plus_global_reset`(
	`id` int unsigned NOT NULL DEFAULT 1,
	`last_reset_time` BIGINT UNSIGNED NOT NULL DEFAULT 0,
	PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- 初始化记录（使用当前时间）
INSERT INTO `mythic_plus_global_reset` (`id`, `last_reset_time`) VALUES (1, UNIX_TIMESTAMP());
