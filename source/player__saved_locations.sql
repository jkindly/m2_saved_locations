SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for saved_locations
-- ----------------------------
DROP TABLE IF EXISTS `saved_locations`;
CREATE TABLE `saved_locations` (
  `pid` int(11) DEFAULT NULL,
  `idx` tinyint(4) DEFAULT NULL,
  `global_x` int(11) DEFAULT NULL,
  `global_y` int(11) DEFAULT NULL,
  `local_x` int(11) DEFAULT NULL,
  `local_y` int(11) DEFAULT NULL,
  `name` varchar(26) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
SET FOREIGN_KEY_CHECKS=1;
