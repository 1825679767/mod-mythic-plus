DROP TABLE IF EXISTS `_WY神话_等级奖励`;
CREATE TABLE `_WY神话_等级奖励`(
	`等级` int unsigned NOT NULL,
	`奖励类型` smallint unsigned NOT NULL,
	`参数1` int unsigned NOT NULL,
	`参数2` int unsigned
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (1, 0, 1000000, null);
INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (1, 1, 29434, 1);
INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (2, 0, 4000000, null);
INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (2, 1, 29434, 2);
INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (3, 0, 8000000, null);
INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (3, 1, 29434, 5);
INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (4, 0, 10000000, null);
INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (4, 1, 29434, 10);
INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (5, 0, 15000000, null);
INSERT INTO `_WY神话_等级奖励` (`等级`, `奖励类型`, `参数1`, `参数2`) VALUES (5, 1, 29434, 20);
