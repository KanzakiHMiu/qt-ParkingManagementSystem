/*
 Navicat Premium Data Transfer

 Source Server         : Mysql
 Source Server Type    : MySQL
 Source Server Version : 80300
 Source Host           : localhost:3306
 Source Schema         : parking_management_system

 Target Server Type    : MySQL
 Target Server Version : 80300
 File Encoding         : 65001

 Date: 28/05/2024 08:34:57
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for parking_spots
-- ----------------------------
DROP TABLE IF EXISTS `parking_spots`;
CREATE TABLE `parking_spots`  (
  `spot_id` int NOT NULL AUTO_INCREMENT,
  `spot_number` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `is_available` tinyint(1) NULL DEFAULT 1,
  PRIMARY KEY (`spot_id`) USING BTREE,
  UNIQUE INDEX `spot_number`(`spot_number`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of parking_spots
-- ----------------------------

SET FOREIGN_KEY_CHECKS = 1;
