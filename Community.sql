SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for car
-- ----------------------------
DROP TABLE IF EXISTS `car`;
CREATE TABLE `car` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` varchar(255) NOT NULL,
  `ownerUid` varchar(255) NOT NULL DEFAULT '',
  `isRent` tinyint(1) NOT NULL DEFAULT '0',
  `price` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for owner
-- ----------------------------
DROP TABLE IF EXISTS `owner`;
CREATE TABLE `owner` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` varchar(255) NOT NULL,
  `userName` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `tele` varchar(15) DEFAULT NULL,
  `sex` varchar(255) DEFAULT NULL,
  `status` varchar(255) NOT NULL DEFAULT '业主',
  `power` double(5,0) NOT NULL DEFAULT '1',
  `houseId` varchar(255) NOT NULL DEFAULT '',
  `houseArea` double(25,2) DEFAULT NULL,
  `wantCar` varchar(255) NOT NULL DEFAULT '',
  `agCar` tinyint(1) NOT NULL DEFAULT '0',
  `CarId` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for repair
-- ----------------------------
DROP TABLE IF EXISTS `repair`;
CREATE TABLE `repair` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `ownerUid` varchar(255) NOT NULL,
  `owner` varchar(255) DEFAULT NULL,
  `houseId` varchar(255) NOT NULL,
  `kind` varchar(255) DEFAULT NULL,
  `problem` varchar(255) DEFAULT NULL,
  `submitDate` timestamp NULL DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
  `solveStaff` varchar(255) DEFAULT NULL,
  `teleNum` bigint(20) DEFAULT NULL,
  `state` varchar(255) NOT NULL DEFAULT '待处理',
  `evaluate` tinyint(1) NOT NULL DEFAULT '0',
  `thank` varchar(255) DEFAULT NULL,
  `star` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for staff
-- ----------------------------
DROP TABLE IF EXISTS `staff`;
CREATE TABLE `staff` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` varchar(255) NOT NULL,
  `userName` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `tele` varchar(15) DEFAULT NULL,
  `sex` varchar(255) NOT NULL DEFAULT '男',
  `status` varchar(255) NOT NULL DEFAULT '员工',
  `power` double(5,0) NOT NULL DEFAULT '2',
  `vacation` tinyint(1) NOT NULL DEFAULT '0',
  `attend` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Table structure for vacation
-- ----------------------------
DROP TABLE IF EXISTS `vacation`;
CREATE TABLE `vacation` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `uid` varchar(255) NOT NULL,
  `userName` varchar(255) NOT NULL,
  `kind` varchar(255) NOT NULL,
  `reason` varchar(255) NOT NULL,
  `finish` tinyint(1) NOT NULL DEFAULT '0',
  `agree` tinyint(1) NOT NULL DEFAULT '0',
  `isRead` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=21 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Function structure for staffTest
-- ----------------------------
DROP FUNCTION IF EXISTS `staffTest`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` FUNCTION `staffTest`() RETURNS int(11)
BEGIN
	UPDATE staff SET attend = FALSE;

	RETURN 0;
END
;;
DELIMITER ;

-- ----------------------------
-- Event structure for 时间
-- ----------------------------
DROP EVENT IF EXISTS `时间`;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` EVENT `时间` ON SCHEDULE EVERY 1 DAY STARTS '2018-07-11 00:00:00' ON COMPLETION NOT PRESERVE ENABLE DO UPDATE staff SET attend = FALSE
;;
DELIMITER ;
