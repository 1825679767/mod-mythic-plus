DROP TABLE IF EXISTS `mythic_plus_spell_override`;
CREATE TABLE `mythic_plus_spell_override`(
	`spellid` int unsigned NOT NULL,
	`map` int unsigned NOT NULL,
	`modpct` float default '-1',
	`dotmodpct` float default '-1',
	`comment` varchar(255),
	PRIMARY KEY (`spellid`, `map`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

INSERT INTO `mythic_plus_spell_override` (`spellid`, `map`, `modpct`, `dotmodpct`, `comment`) VALUES (9532,389,3.75, -1,'怒焰萨满 - 闪电箭');
INSERT INTO `mythic_plus_spell_override` (`spellid`, `map`, `modpct`, `dotmodpct`, `comment`) VALUES (11968,389,18,-1,'熔岩元素 - 火焰护盾');
INSERT INTO `mythic_plus_spell_override` (`spellid`, `map`, `modpct`, `dotmodpct`, `comment`) VALUES (18266,389,-1,8,'炽刃教徒 - 痛苦诅咒');
INSERT INTO `mythic_plus_spell_override` (`spellid`, `map`, `modpct`, `dotmodpct`, `comment`) VALUES (20800,389,5,12,'唤焰者杰克索 - 献祭(持续)');
