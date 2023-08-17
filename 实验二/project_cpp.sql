/*
 Navicat Premium Data Transfer

 Source Server         : localhost
 Source Server Type    : MySQL
 Source Server Version : 80028
 Source Host           : localhost:3306
 Source Schema         : project_cpp

 Target Server Type    : MySQL
 Target Server Version : 80028
 File Encoding         : 65001

 Date: 26/06/2022 22:03:41
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for delivery_improve
-- ----------------------------
DROP TABLE IF EXISTS `delivery_improve`;
CREATE TABLE `delivery_improve`  (
  `number` int NOT NULL,
  `sender` int NOT NULL,
  `receiver` int NOT NULL,
  `time_send` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `time_receive` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `weight` int NOT NULL,
  `cost` double(10, 6) NOT NULL,
  `goodstate` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `discription` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `courier` int NOT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of delivery_improve
-- ----------------------------
INSERT INTO `delivery_improve` VALUES (1, 1, 3, '2022-4-7-3-38-30', '', 1, 8.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (2, 1, 2, '2022-4-7-23-40-50', '', 1, 8.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (3, 1, 3, '2022-4-20-5-8-50', '2022-2-28-16-17-50', 1, 2.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (4, 1, 3, '2022-4-25-8-22-20', '2022-3-16-0-50-50', 1, 2.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (5, 1, 3, '2022-4-25-8-48-40', '', 1, 5.000000, '2', '', 0);
INSERT INTO `delivery_improve` VALUES (6, 1, 2, '2022-4-25-10-1-0', '', 1, 2.000000, '2', '瓜子书', 1);
INSERT INTO `delivery_improve` VALUES (7, 3, 1, '2022-4-25-12-49-0', '2022-3-26-9-36-0', 1, 5.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (8, 1, 4, '2022-3-24-11-17-20', '', 1, 2.000000, '2', '', 0);
INSERT INTO `delivery_improve` VALUES (9, 1, 4, '2022-3-24-11-41-50', '', 1, 8.000000, '2', '', 0);
INSERT INTO `delivery_improve` VALUES (10, 1, 2, '2022-3-24-12-45-10', '', 1, 5.000000, '2', '瓜子', 0);
INSERT INTO `delivery_improve` VALUES (11, 1, 5, '2022-3-24-15-48-0', '', 1, 8.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (12, 1, 5, '2022-3-24-16-14-50', '', 1, 2.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (13, 1, 3, '2022-3-24-16-37-30', '', 1, 5.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (14, 1, 2, '2022-3-24-17-4-40', '', 1, 2.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (15, 1, 3, '2022-3-24-20-31-20', '', 1, 5.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (16, 1, 3, '2022-3-25-9-34-20', '', 1, 2.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (17, 1, 5, '2022-3-25-18-29-40', '', 1, 5.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (18, 3, 2, '2022-2-28-18-13-20', '', 1, 2.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (19, 1, 2, '2022-3-1-0-23-30', '2022-3-11-9-10-0', 1, 2.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (20, 2, 5, '2022-3-1-2-30-50', '', 1, 2.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (21, 1, 3, '2022-3-2-19-31-20', '', 1, 2.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (22, 1, 4, '2022-3-2-20-33-10', '', 1, 2.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (23, 1, 4, '2022-3-2-22-14-50', '', 1, 8.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (24, 1, 4, '2022-3-2-22-47-10', '', 1, 5.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (25, 1, 4, '2022-3-3-18-12-0', '', 1, 5.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (26, 1, 5, '2022-3-7-4-28-10', '', 1, 2.000000, '2', '', 1);
INSERT INTO `delivery_improve` VALUES (27, 1, 3, '2022-3-7-7-7-10', '', 1, 5.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (28, 1, 6, '2022-3-7-8-10-40', '', 1, 8.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (29, 1, 4, '2022-3-8-16-46-10', '', 1, 2.000000, '2', '123', 1);
INSERT INTO `delivery_improve` VALUES (30, 1, 4, '2022-3-9-3-45-40', '', 1, 5.000000, '2', '%', 1);
INSERT INTO `delivery_improve` VALUES (31, 1, 4, '2022-3-3-0-2-10', '', 1, 2.000000, '2', '', 0);
INSERT INTO `delivery_improve` VALUES (32, 1, 6, '2022-3-6-12-12-0', '', 3, 6.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (33, 1, 5, '2022-3-10-20-50-50', '', 8, 64.000000, '2', '多窗口测试', 0);
INSERT INTO `delivery_improve` VALUES (34, 1, 3, '2022-3-9-7-34-40', '', 4, 8.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (35, 1, 6, '2022-3-9-9-18-0', '', 10, 80.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (36, 1, 6, '2022-3-9-17-29-0', '', 3, 24.000000, '2', '', 0);
INSERT INTO `delivery_improve` VALUES (37, 1, 5, '2022-3-9-22-42-50', '', 3, 6.000000, '2', '', 0);
INSERT INTO `delivery_improve` VALUES (38, 1, 5, '2022-3-11-8-30-20', '', 2, 4.000000, '2', '', 2);
INSERT INTO `delivery_improve` VALUES (39, 1, 5, '2022-3-16-5-45-0', '', 2, 4.000000, '2', '', 0);
INSERT INTO `delivery_improve` VALUES (40, 1, 5, '2022-3-17-9-41-30', '', 10, 80.000000, '2', '用户管理员测试', 0);
INSERT INTO `delivery_improve` VALUES (41, 1, 6, '2022-3-22-4-34-20', '', 5, 40.000000, '2', 'test', 2);
INSERT INTO `delivery_improve` VALUES (42, 1, 6, '2022-3-23-1-52-10', '', 4, 8.000000, '0', '17：19test', 0);
INSERT INTO `delivery_improve` VALUES (43, 1, 3, '2022-3-23-4-18-0', '', 2, 4.000000, '0', '', 0);
INSERT INTO `delivery_improve` VALUES (44, 1, 5, '2022-3-23-4-20-40', '', 2, 4.000000, '0', '', 0);
INSERT INTO `delivery_improve` VALUES (45, 1, 7, '2022-3-23-4-24-20', '', 2, 16.000000, '0', '', 0);
INSERT INTO `delivery_improve` VALUES (46, 1, 6, '2022-3-20-14-47-10', '', 2, 4.000000, '0', 'test', 0);
INSERT INTO `delivery_improve` VALUES (47, 1, 4, '2022-3-20-22-1-50', '', 3, 15.000000, '0', '', 0);
INSERT INTO `delivery_improve` VALUES (48, 1, 6, '2022-3-21-1-59-20', '', 5, 25.000000, '0', '', 0);
INSERT INTO `delivery_improve` VALUES (49, 1, 3, '2022-3-23-12-15-30', '', 10, 80.000000, '0', 'testtest', 0);

-- ----------------------------
-- Table structure for deliverys
-- ----------------------------
DROP TABLE IF EXISTS `deliverys`;
CREATE TABLE `deliverys`  (
  `number` int NOT NULL,
  `sender` int NOT NULL,
  `receiver` int NOT NULL,
  `time_send` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `time_receive` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `goodstate` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `cost` double(10, 6) NOT NULL,
  `discription` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of deliverys
-- ----------------------------
INSERT INTO `deliverys` VALUES (1, 1, 4, '2022-3-15-10-37-10', '2022-3-15-11-25-10', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (2, 1, 4, '2022-3-15-10-47-50', '2022-3-15-11-36-40', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (3, 1, 4, '2022-3-15-10-58-50', '2022-3-15-11-40-30', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (4, 1, 4, '2022-3-17-10-5-0', '2022-3-28-15-6-20', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (5, 1, 4, '2022-3-17-10-14-30', '2022-4-3-10-15-40', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (6, 1, 4, '2022-3-17-10-24-20', '2022-4-3-10-17-40', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (7, 1, 4, '2022-3-17-10-38-50', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (8, 1, 4, '2022-3-17-10-48-40', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (9, 1, 3, '2022-3-19-20-28-50', '2022-4-13-3-18-0', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (10, 1, 3, '2022-3-22-11-59-30', '2022-4-19-4-39-50', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (11, 1, 3, '2022-3-22-12-10-30', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (12, 1, 3, '2022-3-22-12-20-30', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (13, 1, 3, '2022-3-22-12-30-50', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (14, 1, 2, '2022-3-3-0-9-10', '2022-4-3-9-40-10', '2', 15.000000, '给你买的瓜子');
INSERT INTO `deliverys` VALUES (15, 1, 4, '2022-3-5-14-16-0', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (16, 1, 2, '2022-3-16-0-50-30', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (17, 1, 2, '2022-3-15-7-36-20', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (18, 1, 3, '2022-3-15-7-32-10', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (19, 1, 3, '2022-4-3-2-58-50', '2022-4-3-10-46-50', '2', 15.000000, '一艘军舰');
INSERT INTO `deliverys` VALUES (20, 1, 3, '2022-4-3-3-36-10', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (21, 1, 4, '2022-4-3-3-52-0', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (22, 1, 2, '2022-4-3-4-13-0', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (23, 1, 3, '2022-4-3-6-6-50', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (24, 1, 2, '2022-4-3-6-22-40', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (25, 1, 4, '2022-4-3-6-37-50', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (26, 3, 1, '2022-4-4-1-26-20', '2022-4-4-18-46-40', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (27, 3, 4, '2022-4-4-1-42-20', '2022-4-19-16-28-20', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (28, 3, 1, '2022-4-4-2-0-0', '2022-4-4-18-55-40', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (29, 3, 1, '2022-4-4-2-17-30', '2022-4-4-18-51-50', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (30, 3, 1, '2022-4-4-2-32-10', '2022-4-4-19-2-0', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (31, 3, 2, '2022-4-4-2-49-10', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (32, 3, 1, '2022-4-4-3-5-20', '2022-4-4-7-17-20', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (33, 3, 1, '2022-4-4-3-20-10', '2022-4-4-7-8-0', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (34, 3, 1, '2022-4-4-3-34-50', '2022-4-4-18-58-0', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (35, 3, 1, '2022-4-4-3-47-50', '2022-4-4-19-4-10', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (36, 3, 2, '2022-4-4-4-2-40', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (37, 3, 1, '2022-4-4-4-19-0', '2022-4-4-19-6-20', '2', 15.000000, '');
INSERT INTO `deliverys` VALUES (38, 1, 4, '2022-4-6-8-53-50', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (39, 1, 2, '2022-4-6-11-25-50', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (40, 1, 2, '2022-4-6-17-38-40', '', '1', 15.000000, '123');
INSERT INTO `deliverys` VALUES (41, 3, 2, '2022-4-13-10-58-40', '', '1', 15.000000, '12345');
INSERT INTO `deliverys` VALUES (42, 1, 5, '2022-4-14-17-52-0', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (43, 1, 5, '2022-4-18-2-23-40', '', '1', 15.000000, '');
INSERT INTO `deliverys` VALUES (44, 1, 5, '2022-4-22-8-57-10', '2022-4-22-17-29-50', '2', 15.000000, 'test');
INSERT INTO `deliverys` VALUES (45, 2, 4, '2022-4-26-8-19-40', '', '1', 15.000000, '');

SET FOREIGN_KEY_CHECKS = 1;
