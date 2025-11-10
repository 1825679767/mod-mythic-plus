DROP TABLE IF EXISTS `_WY神话_等级配置`;
CREATE TABLE `_WY神话_等级配置`(
	`等级` int unsigned NOT NULL,
	`时间限制` int unsigned NOT NULL,
	`随机词缀数量` int unsigned DEFAULT '0',
	PRIMARY KEY (`等级`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

INSERT INTO `_WY神话_等级配置` (`等级`, `时间限制`, `随机词缀数量`) VALUES (1, 60*45, 0);
INSERT INTO `_WY神话_等级配置` (`等级`, `时间限制`, `随机词缀数量`) VALUES (2, 60*45, 0);
INSERT INTO `_WY神话_等级配置` (`等级`, `时间限制`, `随机词缀数量`) VALUES (3, 60*40, 0);
INSERT INTO `_WY神话_等级配置` (`等级`, `时间限制`, `随机词缀数量`) VALUES (4, 60*40, 0);
INSERT INTO `_WY神话_等级配置` (`等级`, `时间限制`, `随机词缀数量`) VALUES (5, 60*40, 0);
