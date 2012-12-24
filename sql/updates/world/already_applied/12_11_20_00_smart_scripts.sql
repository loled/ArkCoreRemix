/*
SQLyog Community v10.3 
MySQL - 5.5.24-0ubuntu0.12.04.1 : Database - 22dev_ark
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
/*Table structure for table `smart_scripts` */

DROP TABLE IF EXISTS `smart_scripts`;

CREATE TABLE `smart_scripts` (
  `entryorguid` mediumint(11) NOT NULL,
  `source_type` mediumint(5) unsigned NOT NULL DEFAULT '0',
  `id` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `link` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_type` mediumint(5) unsigned NOT NULL DEFAULT '0',
  `event_phase_mask` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_chance` mediumint(5) unsigned NOT NULL DEFAULT '100',
  `event_flags` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_param1` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_param2` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_param3` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `event_param4` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_type` mediumint(5) unsigned NOT NULL DEFAULT '0',
  `action_param1` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param2` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param3` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param4` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param5` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `action_param6` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_type` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_param1` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_param2` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_param3` mediumint(11) unsigned NOT NULL DEFAULT '0',
  `target_x` float NOT NULL DEFAULT '0',
  `target_y` float NOT NULL DEFAULT '0',
  `target_z` float NOT NULL DEFAULT '0',
  `target_o` float NOT NULL DEFAULT '0',
  `comment` varchar(255) NOT NULL DEFAULT '' COMMENT 'Event Comment',
  PRIMARY KEY (`entryorguid`,`source_type`,`id`,`link`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 ROW_FORMAT=FIXED COMMENT='CTDB Smart Scripts';

/*Data for the table `smart_scripts` */


/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;