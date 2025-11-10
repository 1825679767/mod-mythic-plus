DROP TABLE IF EXISTS `_WY神话_词缀配置`;
CREATE TABLE `_WY神话_词缀配置`(
	`等级` int unsigned NOT NULL,
	`词缀类型` smallint unsigned NOT NULL,
	`参数1` float,
	`参数2` float
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (1, 1, 0.15);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (2, 1, 0.15);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (2, 2, 0.1);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (2, 4, 10);

INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (3, 1, 0.2);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (3, 2, 0.15);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (3, 3, 15);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (3, 4, 20);

INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (4, 1, 0.2);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (4, 2, 0.15);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (4, 3, 30);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (4, 4, 30);

INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (5, 1, 0.2);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (5, 2, 0.15);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (5, 3, 30);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (5, 4, 30);
INSERT INTO `_WY神话_词缀配置` (`等级`, `词缀类型`, `参数1`) VALUES (5, 5, null);
