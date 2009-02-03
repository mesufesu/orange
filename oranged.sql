-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	6.0.8-alpha-community


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema oranged
--

CREATE DATABASE IF NOT EXISTS oranged;
USE oranged;

--
-- Definition of table `accounts`
--

DROP TABLE IF EXISTS `accounts`;
CREATE TABLE `accounts` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `account` char(10) NOT NULL,
  `password` char(10) NOT NULL,
  `status` int(10) unsigned NOT NULL DEFAULT '0',
  `gmlevel` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`,`account`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `accounts`
--

/*!40000 ALTER TABLE `accounts` DISABLE KEYS */;
INSERT INTO `accounts` (`id`,`account`,`password`,`status`,`gmlevel`) VALUES 
 (1,'amb5','test',0,0);
/*!40000 ALTER TABLE `accounts` ENABLE KEYS */;


--
-- Definition of table `character_inventory`
--

DROP TABLE IF EXISTS `character_inventory`;
CREATE TABLE `character_inventory` (
  `item_guid` int(10) unsigned NOT NULL,
  `guid` int(10) unsigned NOT NULL,
  `slot` int(10) unsigned NOT NULL,
  PRIMARY KEY (`item_guid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `character_inventory`
--

/*!40000 ALTER TABLE `character_inventory` DISABLE KEYS */;
/*!40000 ALTER TABLE `character_inventory` ENABLE KEYS */;


--
-- Definition of table `character_items`
--

DROP TABLE IF EXISTS `character_items`;
CREATE TABLE `character_items` (
  `item_guid` int(10) unsigned NOT NULL,
  `type` int(11) NOT NULL,
  `level` int(10) unsigned NOT NULL DEFAULT '0',
  `durability` double NOT NULL DEFAULT '0',
  `option1` int(10) unsigned NOT NULL DEFAULT '0',
  `option2` int(10) unsigned NOT NULL DEFAULT '0',
  `option3` int(10) unsigned NOT NULL DEFAULT '0',
  `newoption` int(10) unsigned NOT NULL DEFAULT '0',
  `setoption` int(10) unsigned NOT NULL DEFAULT '0',
  `petitem_level` int(10) unsigned NOT NULL DEFAULT '0',
  `petitem_exp` int(10) unsigned NOT NULL DEFAULT '0',
  `joh_option` int(10) unsigned NOT NULL DEFAULT '0',
  `optionex` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`item_guid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


--
-- Definition of table `characters`
--

DROP TABLE IF EXISTS `characters`;
CREATE TABLE `characters` (
  `guid` int(10) unsigned NOT NULL,
  `account` char(10) NOT NULL,
  `name` char(10) NOT NULL,
  `class` int(10) unsigned NOT NULL DEFAULT '0',
  `changeup` int(10) unsigned NOT NULL DEFAULT '0',
  `position` int(10) unsigned NOT NULL DEFAULT '0',
  `experience` bigint(20) unsigned NOT NULL DEFAULT '0',
  `leveluppoint` int(10) unsigned NOT NULL DEFAULT '0',
  `level` int(10) unsigned NOT NULL DEFAULT '1',
  `strength` int(10) unsigned NOT NULL DEFAULT '0',
  `dexterity` int(10) unsigned NOT NULL DEFAULT '0',
  `vitality` int(10) unsigned NOT NULL DEFAULT '0',
  `energy` int(10) unsigned NOT NULL DEFAULT '0',
  `leadership` int(10) unsigned NOT NULL DEFAULT '0',
  `life` int(11) NOT NULL DEFAULT '0',
  `mana` int(11) NOT NULL DEFAULT '0',
  `shield` int(11) NOT NULL DEFAULT '0',
  `bp` int(11) NOT NULL DEFAULT '0',
  `money` int(10) unsigned NOT NULL DEFAULT '0',
  `pklevel` int(10) unsigned NOT NULL DEFAULT '0',
  `addpoint` int(10) unsigned NOT NULL DEFAULT '0',
  `maxaddpoint` int(10) unsigned NOT NULL DEFAULT '0',
  `minuspoint` int(10) unsigned NOT NULL DEFAULT '0',
  `maxminuspoint` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`name`,`guid`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Definition of table `item_template`
--

DROP TABLE IF EXISTS `item_template`;
CREATE TABLE `item_template` (
  `type` int(10) unsigned NOT NULL,
  `slot` int(11) NOT NULL,
  `skill` int(10) unsigned NOT NULL,
  `width` int(10) unsigned NOT NULL,
  `height` int(10) unsigned NOT NULL,
  `option` tinyint(1) NOT NULL DEFAULT '0',
  `drop` tinyint(1) NOT NULL DEFAULT '0',
  `name` char(32) NOT NULL,
  `level` int(10) unsigned NOT NULL,
  `reqlevel` int(10) unsigned NOT NULL,
  `durability` int(10) unsigned NOT NULL,
  `SPECIAL` bigint(20) unsigned NOT NULL,
  `strength` int(10) unsigned NOT NULL,
  `dexterity` int(10) unsigned NOT NULL,
  `energy` int(10) unsigned NOT NULL,
  `vitality` int(10) unsigned NOT NULL,
  `leadership` int(10) unsigned NOT NULL,
  `set_option` int(10) unsigned NOT NULL,
  `CLASS_ATTR` int(10) unsigned NOT NULL,
  PRIMARY KEY (`type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `item_template`
--

/*!40000 ALTER TABLE `item_template` DISABLE KEYS */;
INSERT INTO `item_template` (`type`,`slot`,`skill`,`width`,`height`,`option`,`drop`,`name`,`level`,`reqlevel`,`durability`,`SPECIAL`,`strength`,`dexterity`,`energy`,`vitality`,`leadership`,`set_option`,`CLASS_ATTR`) VALUES 
 (0,0,0,1,2,1,1,'©¸®½º',6,0,20,25957629952,40,40,0,0,0,1,4681),
 (1,0,0,1,3,1,1,'ªÀº°Ë',3,0,22,13003653120,60,0,0,0,0,1,4681),
 (2,0,0,1,3,1,1,'¹ÀÌÇÇ¾î',9,0,23,38908985344,50,40,0,0,0,1,4680),
 (3,0,20,1,3,1,1,'«Å¸Ä¡',16,0,27,69157978112,80,40,0,0,0,1,4616),
 (4,0,21,1,3,1,1,'Ú°´°Ë',12,0,24,51843563520,60,40,0,0,0,1,4616),
 (5,0,22,1,3,1,1,'í·¹ÀÌµå',36,0,39,155409317888,80,50,0,0,0,1,4681),
 (6,0,20,1,3,1,1,'×¶óµð¿ì½º',20,0,30,86403973120,110,0,0,0,0,1,4680),
 (7,0,21,1,3,1,1,'Þ¼Ç',24,0,34,103651278848,120,0,0,0,0,1,4616),
 (8,0,21,1,3,1,1,'­ÆæÆ®º¼±×',30,0,36,129521418240,130,0,0,0,0,1,4616),
 (9,0,20,2,3,1,1,'¿·¯¸à´õ°Ë',32,0,40,138212671488,103,0,0,0,0,1,520),
 (10,0,22,2,4,1,1,'ûÀÇ°Ë',40,0,50,202888511488,80,60,0,0,0,1,584),
 (11,0,20,2,3,1,1,'ü¼³ÀÇ°Ë',44,0,54,241727438848,120,0,0,0,0,1,520),
 (13,0,22,1,3,1,1,'õºíºí·¹ÀÌµå',48,0,43,207099920384,70,70,0,0,0,1,584),
 (12,0,19,2,3,1,1,'Â¾ç°Ë',56,0,66,315178418176,140,0,0,0,0,1,520),
 (14,0,22,1,3,1,1,'ø°³°Ë',59,0,50,254529110016,90,50,0,0,0,1,584),
 (15,0,23,2,3,1,1,'Å´ëÇÑ°Ë',52,0,60,259125411840,140,0,0,0,0,1,520),
 (16,0,22,1,4,1,1,'Ä±«ÀÇ°Ë',82,0,84,353699561472,160,60,0,0,0,1,520),
 (17,0,23,2,4,1,1,'ÙÅ©ºê·¹ÀÌÄ¿',104,0,89,552325349376,180,50,0,0,0,1,16),
 (18,0,23,2,3,1,1,'±´õºí·¹ÀÌµå',105,0,86,604116615168,180,50,0,0,0,1,512),
 (19,0,22,1,4,1,0,'ëÃµ»çÀÇÀý´ë°Ë',86,0,168,517579407360,140,50,0,0,0,0,4616),
 (31,0,56,2,4,1,1,'¥½ººê·Îµå',100,0,93,448859930728,135,62,9,0,0,3,512),
 (20,0,22,1,4,1,1,'ªÀÌÆ®ºí·¹ÀÌµå',140,0,90,461493174272,116,38,0,0,0,1,16),
 (21,0,56,2,4,1,1,'¥½ººí·¹ÀÌµå',140,0,100,496306225267,116,53,9,0,0,1,512),
 (22,0,22,1,4,1,1,'»ºí·¹ÀÌµå',147,380,95,526253555712,100,35,0,0,0,0,16),
 (23,0,56,2,4,1,1,'Í½ºÇÃ·ÎÀüºí·¹ÀÌµå',147,380,110,548064264326,98,48,7,0,0,0,512),
 (24,0,22,2,4,1,1,'¥ÀÌºê·¹ÀÌÅ©',115,0,90,785344102400,192,30,0,0,0,0,16),
 (25,0,56,2,4,1,1,'Òµå´í¼­',115,0,90,470435758188,136,57,9,0,0,0,512),
 (512,0,0,1,3,1,1,'ÛÀºµµ³¢',1,0,18,4396941312,50,0,0,0,0,1,4681),
 (513,0,0,1,3,1,1,'Õµµ³¢',4,0,20,17332830208,70,0,0,0,0,1,4681),
 (514,0,19,1,3,1,1,'ç³¯µµ³¢',14,0,26,60533506048,90,0,0,0,0,1,4616),
 (515,0,19,1,3,1,1,'ä¸¶È£Å©',18,0,28,77781139456,100,0,0,0,0,1,4616),
 (516,0,0,1,3,1,1,'äÁ¤µµ³¢',26,0,32,112309305344,50,70,0,0,0,1,577),
 (517,0,19,2,3,1,1,'üÅõµµ³¢',30,0,36,155358330880,120,0,0,0,0,1,584),
 (518,0,19,2,3,1,1,'ÏÄÉ¾Æµµ³¢',34,0,44,164049584128,130,0,0,0,0,1,584),
 (519,0,19,2,3,1,1,'ó¸£Ä­µµ³¢',46,0,55,233053945856,140,0,0,0,0,1,520),
 (520,0,19,2,3,1,1,'Ý¿ùµµ³¢',54,0,65,297847881728,100,40,0,0,0,1,521),
 (1024,0,0,1,3,1,1,'ü°ï',7,0,21,30283857920,100,0,0,0,0,1,4616),
 (1025,0,19,1,3,1,1,'ð´×½ºÅ¸',13,0,25,56204656640,100,0,0,0,0,1,4616),
 (1026,0,0,1,3,1,1,'¶Åð',22,0,32,95027134464,80,50,0,0,0,1,4616),
 (1027,0,19,2,3,1,1,'×·¹ÀÌÆ®ÇØ¸Ó',38,0,50,194214035456,150,0,0,0,0,1,520),
 (1028,0,19,2,3,1,1,'©¸®½ºÅ»¸ð´×½ºÅ¸',66,0,72,336804577280,130,0,0,0,0,1,585),
 (1029,0,23,2,4,1,1,'©¸®½ºÅ»°Ë',72,0,76,384267976704,130,70,0,0,0,1,585),
 (1030,0,23,2,4,1,0,'«¿À½ºµå¶ó°ïµµ³¢',75,0,80,440269996032,140,50,0,0,0,0,520),
 (1031,0,0,1,3,1,1,'¤¸®¸àÅ»¸ÞÀÌ½º',90,0,50,267633426432,15,42,0,0,0,1,128),
 (1032,0,66,1,3,1,1,'£Æ²¼ÁÅÍ',54,0,40,176969023491,80,17,0,0,0,1,4096),
 (1033,0,66,1,3,1,1,'¶½ºÅÍ¼ÁÅÍ',72,0,45,245956935700,87,18,0,0,0,1,4096),
 (1034,0,66,1,4,1,1,'×·¹ÀÌÆ®¼ÁÅÍ',82,0,65,319256592419,100,21,0,0,0,1,4096),
 (1035,0,66,1,4,1,1,'Îµå¼ÁÅÍ',98,0,72,392555921460,105,23,0,0,0,1,4096),
 (1036,0,66,1,4,1,1,'×·¹ÀÌÆ®·Îµå¼ÁÅÍ',140,0,84,465872355395,90,20,0,0,0,1,4096),
 (1037,0,66,1,4,1,0,'ëÃµ»çÀÇÀý´ë¼ÁÅÍ',150,0,90,517797838926,75,16,0,0,0,1,4096),
 (1038,0,66,1,4,1,1,'Ö·¹ÀÌÀ¯¼ÁÅÍ',146,380,95,560915284052,80,15,0,0,0,0,4096),
 (1039,0,66,1,4,1,1,'þÀÌ´×¼ÁÅÍ',110,0,78,427066654780,108,22,0,0,0,0,4096),
 (1536,0,22,2,4,1,1,'¤¼±ºÀ',42,0,56,215806967808,60,70,0,0,0,1,584),
 (1537,0,0,2,4,1,1,'¢',23,0,42,129538850816,70,50,0,0,0,1,584),
 (1538,0,0,2,4,1,1,'å·¡°Ç·£½º',15,0,34,90749927424,70,50,0,0,0,1,584),
 (1539,0,0,2,4,1,1,'«»ïÁöÃ¢',29,0,44,151046914048,90,30,0,0,0,1,584),
 (1540,0,20,2,4,1,1,'­ÆæÆ®½ºÇÇ¾î',46,0,58,250451591168,90,30,0,0,0,1,584),
 (1541,0,0,2,4,1,1,'ç³¯µµ³¢Ã¢',13,0,38,82126438400,70,50,0,0,0,1,584),
 (1542,0,0,2,4,1,1,'µ³¢Ã¢',19,0,40,107963351040,70,50,0,0,0,1,584),
 (1543,0,22,2,4,1,1,'öµð½´',37,0,54,181296562176,80,50,0,0,0,1,584),
 (1544,0,22,2,4,1,1,'×·¹ÀÌÆ®»çÀÌµå',54,0,68,306487820288,90,50,0,0,0,1,584),
 (1545,0,22,2,4,1,1,'ß·ÏÀÇ³´',63,0,74,328130428928,80,50,0,0,0,1,584),
 (1546,0,22,2,4,1,1,'å¶ó°ï½ºÇÇ¾î',92,0,85,483387441152,170,60,0,0,0,1,16),
 (2048,1,24,2,3,1,1,'ÜÈ°',2,0,20,12970754048,20,80,0,0,0,2,64),
 (2049,1,24,2,3,1,1,'°',8,0,24,38874775552,30,90,0,0,0,2,64),
 (2050,1,24,2,3,1,1,'äÁ¤È°',16,0,28,73419063296,30,90,0,0,0,2,64),
 (2051,1,24,2,3,1,1,'üÅõÈ°',26,0,36,120881807360,30,90,0,0,0,2,64),
 (2052,1,24,2,4,1,1,'¸ÀÌ°Åº¸¿ì',40,0,43,181263007744,30,100,0,0,0,2,64),
 (2053,1,24,2,4,1,1,'Ç¹öº¸¿ì',56,0,48,254596874240,30,100,0,0,0,2,64),
 (2054,1,24,2,4,1,0,'«¿À½º³×ÀÌÃÄº¸¿ì',75,0,68,379737800704,40,150,0,0,0,0,64),
 (2055,1,0,1,1,0,0,'®±Ã¿ëÈ­»ì',0,0,255,0,0,0,0,0,0,0,64),
 (2056,0,24,2,2,1,1,'®±Ã',4,0,22,21611675648,20,90,0,0,0,2,64),
 (2057,0,24,2,2,1,1,'²±Ý¼®±Ã',12,0,26,56155963392,30,90,0,0,0,2,64),
 (2058,0,24,2,2,1,1,'ÆÅ¥¹ö½º',20,0,31,94995218432,30,90,0,0,0,2,64),
 (2059,0,24,2,3,1,1,'ûÀÇ¼®±Ã',32,0,40,151064674304,30,90,0,0,0,2,64),
 (2060,0,24,2,3,1,1,'­ÆÒÆ®¼®±Ã',48,0,45,215774396416,30,100,0,0,0,2,64),
 (2061,0,24,2,3,1,1,'í·çÀ®¼®±Ã',68,0,56,293436129280,40,110,0,0,0,2,64),
 (2062,0,24,2,3,1,1,'ÆÄí¾Æ°ñµå¼®±Ã',72,0,60,336552919040,50,130,0,0,0,2,64),
 (2063,0,0,1,1,0,0,'­»ì',0,0,255,0,0,0,0,0,0,0,64),
 (2064,0,24,2,4,1,1,'¼ÀÎÆ®Å©·Î½º¼®±Ã',84,0,72,440219664384,50,160,0,0,0,2,64),
 (2065,1,24,2,4,1,1,'¦¸®»çÀÌÆ®º¸¿ì',92,0,76,548063608832,54,198,0,0,0,2,128),
 (2066,0,24,2,3,1,0,'ëÃµ»çÀÇÀý´ë¼®±Ã',100,0,200,621262602240,40,110,0,0,0,0,64),
 (2067,0,24,2,3,1,1,'×·¹ÀÌÆ®·¹ÀÎ¼®±Ã',100,0,80,647133396992,61,285,0,0,0,2,128),
 (2068,1,24,2,4,1,1,'¡·Î¿ì¹ÙÀÌÆÛº¸¿ì',135,0,86,716155191296,52,245,0,0,0,2,128),
 (2069,1,24,2,4,1,1,'ÇÇÁÀ©µåº¸¿ì',147,380,93,763567603712,46,210,0,0,0,0,128),
 (2070,1,24,2,4,1,1,'Ë¹ÙÆ®·Î½ºº¸¿ì',110,0,70,668692447232,60,265,0,0,0,0,128),
 (2560,0,0,1,3,1,1,'Ø°ñÁöÆÎÀÌ',6,0,0,12953326598,40,0,0,0,0,3,513),
 (2561,0,0,2,3,1,1,'µ»çÁöÆÎÀÌ',18,0,0,43152647700,50,0,0,0,0,3,513),
 (2562,0,0,2,3,1,1,'¶»çÁöÆÎÀÌ',30,0,0,73318085154,50,0,0,0,0,3,513),
 (2563,0,0,2,4,1,1,'ø°³ÁöÆÎÀÌ',42,0,0,99205332014,40,10,0,0,0,3,513),
 (2564,0,0,2,4,1,1,'í¸£°ïÁöÆÎÀÌ',52,0,0,125092577594,50,0,0,0,0,3,513),
 (2565,0,0,1,4,1,1,'ü¼³ÀÇÁöÆÎÀÌ',59,0,0,125075800635,50,0,0,0,0,3,513),
 (2566,0,0,1,4,1,1,'ÎÈ°ÀÇÁöÆÎÀÌ',70,0,0,150979823174,60,10,0,0,0,3,513),
 (2567,0,0,2,4,1,0,'«¿À½º¹ø°³ÁöÆÎÀÌ',75,0,0,202670753374,60,10,0,0,0,0,513),
 (2568,0,0,2,4,1,1,'Ä¸êÀÇÁöÆÎÀÌ',90,0,0,215656322405,60,10,0,0,0,3,513),
 (2569,0,0,1,4,1,1,'å·¡°ï¼Ò¿ïÁöÆÎÀÌ',100,0,0,198375791452,52,16,0,0,0,3,2),
 (2570,0,0,1,4,1,0,'ëÃµ»çÀÇÀý´ëÁöÆÎÀÌ',104,0,0,228557370986,36,4,0,0,0,0,513),
 (2571,0,0,1,4,1,1,'ïµÐÀÇÁöÆÎÀÌ',140,0,0,237248601966,45,16,0,0,0,0,514),
 (2572,0,0,1,4,1,1,'×·£µå¹ÙÀÌÆÛÁöÆÎÀÌ',147,380,0,284711347330,39,13,0,0,0,0,2),
 (2573,0,0,1,4,1,1,'Ã¶óÆ¼³ªÀ®½ºÅÂÇÁ',110,0,0,219934510712,50,16,0,0,0,0,2);
/*!40000 ALTER TABLE `item_template` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
