DELETE FROM `command` WHERE `name` IN ('mythic', 'mythic reload', 'mythic info');
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('mythic', 0, '语法：.mythic $subcommand
输入 .mythic 查看可用子命令列表。');
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('mythic reload', 3, '重新加载与史诗钥石相关的指定数据表');
INSERT INTO `command` (`name`, `security`, `help`) VALUES ('mythic info', 0, '显示当前史诗钥石信息');
