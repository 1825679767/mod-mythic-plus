-- 添加 last_upgrade_time 字段用于记录玩家上次升级或重置等级的时间
ALTER TABLE `mythic_plus_char_level` ADD COLUMN `last_upgrade_time` BIGINT UNSIGNED NOT NULL DEFAULT 0 AFTER `mythiclevel`;

-- 为现有记录设置当前时间戳
UPDATE `mythic_plus_char_level` SET `last_upgrade_time` = UNIX_TIMESTAMP();
