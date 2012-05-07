##############################
#     Blackrock Caverns      #
#        by Saiifii          #
##############################

SET @NPC_GUID_START := 15810908;

-- Spawns are 100% clean Blizzlike!
DELETE FROM creature WHERE map = 645;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@NPC_GUID_START + 1, 40164, 645, 3, 1, 11686, 0, 162.599, 1085.32, 201.119, 0, 120, 0, 0, 6141, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 2, 40164, 645, 3, 1, 11686, 0, 170.547, 1063.4, 201.141, 0, 120, 0, 0, 6141, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 3, 40164, 645, 3, 1, 11686, 0, 191.233, 1100.16, 201.107, 0, 120, 0, 0, 6141, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 4, 15214, 645, 3, 1, 11686, 0, 239.429, 1105.64, 205.088, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 5, 15214, 645, 3, 1, 11686, 0, 223.804, 1086.13, 205.709, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 6, 15214, 645, 3, 1, 11686, 0, 238.344, 1071.1, 205.106, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 7, 15214, 645, 3, 1, 11686, 0, 209.613, 1095.27, 207.961, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 8, 15214, 645, 3, 1, 11686, 0, 209.793, 1068.68, 205.781, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 9, 15214, 645, 3, 1, 11686, 0, 178.872, 1073.94, 206.057, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 10, 15214, 645, 3, 1, 11686, 0, 192.781, 1088.81, 204.924, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 11, 15214, 645, 3, 1, 11686, 0, 191.778, 1110.02, 205.623, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 12, 39708, 645, 3, 1, 34088, 0, 172.762, 1086.16, 206.114, 2.86234, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 13, 39670, 645, 3, 1, 31796, 0, 249.264, 949.161, 191.787, 3.14159, 120, 0, 0, 6701850, 0, 0, 0, 294912, 0),
(@NPC_GUID_START + 14, 53488, 645, 3, 1, 16925, 0, 213.931, 1128.35, 205.569, 0, 120, 0, 0, 12600, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 15, 39708, 645, 3, 1, 34088, 0, 247.519, 1081.44, 206.339, 0.139626, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 16, 40164, 645, 3, 1, 11686, 0, 252.835, 1095.13, 201.144, 0, 120, 0, 0, 6141, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 17, 40164, 645, 3, 1, 11686, 0, 253.648, 1070.23, 201.134, 0, 120, 0, 0, 6141, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 18, 40164, 645, 3, 1, 11686, 0, 228.082, 1106, 201.129, 0, 120, 0, 0, 6141, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 19, 39980, 645, 3, 1, 34090, 0, 185.266, 960.439, 190.784, 3.10669, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 20, 39985, 645, 3, 1, 34094, 0, 177.868, 960.441, 190.716, 0, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 21, 39985, 645, 3, 1, 34092, 0, 250.559, 991.189, 190.921, 0.0349066, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 22, 39980, 645, 3, 1, 34090, 0, 202.113, 971.877, 190.95, 0.312558, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 23, 39980, 645, 3, 1, 34090, 0, 193.188, 908.507, 191.428, 6.07375, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 24, 39980, 645, 3, 1, 34090, 0, 201.09, 912.913, 190.797, 4.34587, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 25, 39982, 645, 3, 1, 34096, 0, 199.266, 907.125, 190.808, 1.71042, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 26, 39980, 645, 3, 1, 34090, 0, 202.826, 909.719, 190.801, 4.24594, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 27, 39980, 645, 3, 1, 34090, 0, 191.846, 944.014, 190.804, 2.10005, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 28, 39978, 645, 3, 1, 33501, 0, 210.773, 934.078, 191.093, 0.0174533, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 29, 39978, 645, 3, 1, 33501, 0, 212.273, 938.089, 191.114, 5.48033, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 30, 39985, 645, 3, 1, 34092, 0, 215.753, 934.123, 191.202, 3.10669, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 31, 39980, 645, 3, 1, 34090, 0, 180.502, 951.733, 190.763, 1.91986, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 32, 39708, 645, 3, 1, 34088, 0, 210.616, 1045.23, 204.222, 4.84408, 120, 0, 0, 0, 0, 0, 2048, 32832, 12),
(@NPC_GUID_START + 33, 39708, 645, 3, 1, 34089, 0, 207.81, 1046, 204.33, 0.942459, 120, 0, 0, 0, 0, 0, 2048, 32832, 12),
(@NPC_GUID_START + 34, 39665, 645, 3, 1, 33147, 0, 228.863, 949.438, 192.716, 0.105776, 120, 0, 0, 893580, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 35, 39980, 645, 3, 1, 34090, 0, 256.606, 985.045, 190.931, 2.23402, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 36, 39980, 645, 3, 1, 34090, 0, 255.819, 993.389, 190.874, 3.50811, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 37, 39985, 645, 3, 1, 34092, 0, 253.012, 897.257, 191.323, 1.78024, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 38, 39842, 645, 3, 1, 11686, 0, 207.799, 795.649, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 39, 39842, 645, 3, 1, 11686, 0, 213.172, 805.592, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 40, 39842, 645, 3, 1, 11686, 0, 253.085, 812.432, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 41, 39842, 645, 3, 1, 11686, 0, 261.299, 805.469, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 42, 46007, 657, 1, 1, 11686, 0, -737.617, -13.0803, 635.691, 1.73251, 120, 0, 0, 77490, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 43, 46007, 657, 1, 1, 11686, 0, -744.53, 4.80346, 635.683, 1.17066, 120, 0, 0, 77490, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 44, 46007, 657, 1, 1, 11686, 0, -736.813, 21.9184, 635.68, 0.333176, 120, 0, 0, 77490, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 45, 46007, 657, 1, 1, 11686, 0, -719.107, 28.5703, 635.679, 5.91008, 120, 0, 0, 77490, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 46, 46007, 657, 1, 1, 11686, 0, -701.803, 21.1774, 635.679, 4.99154, 120, 0, 0, 77490, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 47, 46007, 657, 1, 1, 11686, 0, -695.2, 3.40621, 635.673, 4.19789, 120, 0, 0, 77490, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 48, 46007, 657, 1, 1, 11686, 0, -720.592, -20.586, 635.683, 2.76334, 120, 0, 0, 77490, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 49, 46007, 657, 1, 1, 11686, 0, -702.977, -13.9857, 635.682, 3.53424, 120, 0, 0, 77490, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 50, 39842, 645, 3, 1, 11686, 0, 231.655, 815.724, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 51, 39842, 645, 3, 1, 11686, 0, 221.278, 811.769, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 52, 39842, 645, 3, 1, 11686, 0, 243.08, 815.823, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 53, 39978, 645, 3, 1, 33501, 0, 250.575, 902.375, 191.736, 5.13127, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 54, 39980, 645, 3, 1, 34090, 0, 256.783, 901.806, 191.287, 4.08407, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 55, 39842, 645, 3, 1, 11686, 0, 267.144, 795.069, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 56, 39842, 645, 3, 1, 11686, 0, 269.156, 784.839, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 57, 39842, 645, 3, 1, 11686, 0, 213.245, 764.531, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 58, 39842, 645, 3, 1, 11686, 0, 205.495, 784.41, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 59, 39842, 645, 3, 1, 11686, 0, 261.51, 764.432, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 60, 39842, 645, 3, 1, 11686, 0, 231.266, 753.472, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 61, 39842, 645, 3, 1, 11686, 0, 221.788, 757.158, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 62, 39842, 645, 3, 1, 11686, 0, 253.181, 757.622, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 63, 39842, 645, 3, 1, 11686, 0, 243.226, 753.58, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 64, 39842, 645, 3, 1, 11686, 0, 266.97, 774.151, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 65, 39698, 645, 3, 1, 31710, 0, 233.83, 794.087, 95.9091, 5.06145, 120, 0, 0, 893580, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 66, 39842, 645, 3, 1, 11686, 0, 207.668, 774.214, 95.4186, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 67, 39987, 645, 3, 1, 31705, 0, 292.179, 958.434, 191.016, 3.28122, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 68, 39987, 645, 3, 1, 31705, 0, 292.043, 943.946, 190.896, 3.14159, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 69, 39842, 645, 3, 1, 11686, 0, 237.295, 784.776, 95.9924, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 70, 39987, 645, 3, 1, 31705, 0, 366.771, 952.556, 192.167, 3.22886, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 71, 39987, 645, 3, 1, 31705, 0, 378.299, 944.578, 191.93, 3.28122, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 72, 39708, 645, 3, 1, 34088, 0, 470.45, 954.54, 189.238, 6.26919, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 73, 39842, 645, 3, 1, 11686, 0, 573.712, 905.181, 178.154, 0, 120, 0, 0, 42, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 74, 39679, 645, 3, 1, 31546, 0, 573.444, 987.688, 155.354, 4.66003, 120, 0, 0, 893580, 208450, 0, 2048, 32832, 0),
(@NPC_GUID_START + 75, 39987, 645, 3, 1, 31705, 0, 375.255, 949.955, 192.247, 3.26425, 120, 0, 0, 0, 0, 0, 2048, 32832, 12),
(@NPC_GUID_START + 76, 39987, 645, 3, 1, 31705, 0, 375.212, 950.267, 192.252, 3.28919, 120, 0, 0, 0, 0, 0, 2048, 32832, 12),
(@NPC_GUID_START + 77, 39708, 645, 3, 1, 34088, 0, 481.928, 937.62, 183.567, 4.75724, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 78, 39987, 645, 3, 1, 31705, 0, 548.931, 888.587, 169.562, 4.71339, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 79, 39990, 645, 3, 1, 34100, 0, 559.599, 902.392, 155.458, 3.76991, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 80, 39990, 645, 3, 1, 34098, 0, 554.528, 894.991, 155.459, 1.37881, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 81, 39990, 645, 3, 1, 34100, 0, 551.156, 899.227, 155.376, 0.314159, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 82, 39990, 645, 3, 1, 34100, 0, 555.064, 902.663, 155.375, 5.44543, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 83, 39990, 645, 3, 1, 34099, 0, 558.66, 897.497, 155.376, 2.47837, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 84, 39990, 645, 3, 1, 34101, 0, 536.875, 890.715, 157.509, 2.86234, 120, 0, 0, 123804, 39940, 0, 2049, 537166656, 32),
(@NPC_GUID_START + 85, 39990, 645, 3, 1, 34099, 0, 581.288, 910.3, 155.375, 3.42085, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 86, 39990, 645, 3, 1, 34101, 0, 576.444, 927.56, 155.35, 1.55527, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 87, 39990, 645, 3, 1, 34098, 0, 569.516, 927.66, 155.35, 1.55529, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 88, 50284, 645, 3, 1, 34101, 0, 561.962, 983.019, 155.354, 1.55334, 120, 0, 0, 123804, 39940, 0, 2048, 294912, 0),
(@NPC_GUID_START + 89, 39990, 645, 3, 1, 34099, 0, 573.067, 933.609, 155.356, 1.55855, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 90, 39990, 645, 3, 1, 34098, 0, 573.52, 965, 155.25, 1.55638, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 91, 39990, 645, 3, 1, 34101, 0, 577.561, 855.535, 175.548, 4.10152, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 92, 39990, 645, 3, 1, 34098, 0, 583.776, 857.361, 155.511, 1.90241, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 93, 39990, 645, 3, 1, 34100, 0, 579.571, 868.316, 155.477, 5.39307, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 94, 39990, 645, 3, 1, 34099, 0, 578.696, 860.137, 155.474, 0, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 95, 39990, 645, 3, 1, 34100, 0, 588.363, 863.286, 155.504, 2.96706, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 96, 39990, 645, 3, 1, 34098, 0, 579.863, 896.743, 155.376, 2.46091, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 97, 39987, 645, 3, 1, 31705, 0, 598.985, 895.897, 169.562, 4.7189, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 98, 39987, 645, 3, 1, 31705, 0, 556.059, 863.569, 144.136, 3.08465, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 99, 39990, 645, 3, 1, 34101, 0, 470.403, 908.023, 165.835, 5.89921, 120, 0, 0, 123804, 39940, 0, 2049, 537166656, 32),
(@NPC_GUID_START + 100, 39990, 645, 3, 1, 34099, 0, 478.797, 894.821, 165.768, 0.785398, 120, 0, 0, 123804, 39940, 0, 2049, 537166656, 32),
(@NPC_GUID_START + 101, 39990, 645, 3, 1, 34099, 0, 506.464, 892.398, 161.587, 3.75246, 120, 0, 0, 123804, 39940, 0, 2049, 537166656, 32),
(@NPC_GUID_START + 102, 39990, 645, 3, 1, 34100, 0, 521.846, 889.175, 159.96, 2.80998, 120, 0, 0, 123804, 39940, 0, 2049, 537166656, 32),
(@NPC_GUID_START + 103, 39990, 645, 3, 1, 34099, 0, 578.885, 849.097, 175.546, 2.37365, 120, 0, 0, 0, 0, 0, 2048, 32832, 12),
(@NPC_GUID_START + 104, 39990, 645, 3, 1, 34099, 0, 568.052, 856.536, 175.546, 2.81253, 120, 0, 0, 0, 0, 0, 2048, 32832, 12),
(@NPC_GUID_START + 105, 39990, 645, 3, 1, 34100, 0, 566.429, 854.691, 175.546, 1.81715, 120, 0, 0, 0, 0, 0, 2048, 32832, 12),
(@NPC_GUID_START + 106, 39987, 645, 3, 1, 31705, 0, 480.037, 816.546, 113.999, 4.50773, 120, 0, 0, 0, 0, 0, 2048, 32832, 12),
(@NPC_GUID_START + 107, 39987, 645, 3, 1, 31705, 0, 353.22, 812.483, 104.757, 0.0872665, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 108, 39987, 645, 3, 1, 31705, 0, 360.714, 817.781, 105.31, 6.23083, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 109, 39987, 645, 3, 1, 31705, 0, 353.939, 822.736, 104.913, 6.23083, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 110, 39987, 645, 3, 1, 31705, 0, 377.986, 812.945, 104.601, 0.385274, 120, 0, 0, 178755, 0, 0, 2052, 559168, 0),
(@NPC_GUID_START + 111, 39987, 645, 3, 1, 31705, 0, 387.575, 815.917, 103.646, 6.09495, 120, 0, 0, 177000, 0, 0, 2052, 559168, 0),
(@NPC_GUID_START + 112, 39987, 645, 3, 1, 31705, 0, 377.995, 821.071, 104.628, 5.89737, 120, 0, 0, 184351, 0, 0, 2052, 559168, 0),
(@NPC_GUID_START + 113, 51340, 645, 3, 1, 37285, 0, 237.304, 1130.07, 205.652, 3.63028, 120, 0, 0, 64496, 0, 0, 67110912, 0, 0),
(@NPC_GUID_START + 114, 39670, 645, 3, 1, 31796, 0, 375.387, 816.833, 104.786, 3.14158, 120, 0, 0, 6676417, 0, 0, 0, 32768, 0),
(@NPC_GUID_START + 115, 39987, 645, 3, 1, 31705, 0, 328.634, 810.236, 102.942, 0.0872665, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 116, 39987, 645, 3, 1, 31705, 0, 336.127, 815.535, 102.72, 6.23083, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 117, 39987, 645, 3, 1, 31705, 0, 329.352, 820.49, 102.868, 6.23083, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 118, 40004, 645, 3, 1, 33009, 0, 268.007, 813.38, 95.9503, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 119, 40084, 645, 3, 1, 763, 0, 286.611, 754.464, 95.9504, 4.62512, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 120, 40084, 645, 3, 1, 763, 0, 297.356, 767.215, 95.9487, 5.46288, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 121, 40004, 645, 3, 1, 33009, 0, 272.021, 796.469, 95.3664, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 122, 40084, 645, 3, 1, 763, 0, 289.342, 751.747, 95.9504, 3.24631, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 123, 40004, 645, 3, 1, 33009, 0, 247.234, 774.104, 95.9924, 0, 120, 0, 0, 123804, 0, 0, 0, 33587520, 0),
(@NPC_GUID_START + 124, 40004, 645, 3, 1, 33009, 0, 242.852, 747.861, 95.3687, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 125, 40084, 645, 3, 1, 763, 0, 262.017, 731.448, 96.0337, 4.99164, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 126, 40084, 645, 3, 1, 763, 0, 260.194, 739.036, 96.0337, 4.7822, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 127, 40004, 645, 3, 1, 33009, 0, 217.033, 799.224, 95.9091, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 128, 40004, 645, 3, 1, 33009, 0, 227.116, 779.507, 95.9091, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 129, 40004, 645, 3, 1, 33009, 0, 259.226, 751.632, 95.955, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 130, 39994, 645, 3, 1, 12231, 0, 246.781, 767.622, 95.9091, 0.165883, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 131, 40084, 645, 3, 1, 763, 0, 269.026, 735.715, 95.9504, 0.925025, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 132, 40084, 645, 3, 1, 763, 0, 267.637, 740.785, 95.9504, 6.00393, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 133, 40004, 645, 3, 1, 33009, 0, 232.854, 809.17, 95.9091, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 134, 40084, 645, 3, 1, 763, 0, 218.774, 837.194, 95.8674, 2.82743, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 135, 40004, 645, 3, 1, 33009, 0, 222.375, 822.748, 95.9503, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 136, 40004, 645, 3, 1, 33009, 0, 238.637, 828.922, 95.9286, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 137, 40004, 645, 3, 1, 33009, 0, 235.188, 759.477, 95.9091, 0, 120, 0, 0, 123804, 0, 0, 0, 33587520, 0),
(@NPC_GUID_START + 138, 40004, 645, 3, 1, 33009, 0, 252.544, 763.429, 95.9091, 1.274, 120, 0, 0, 123804, 0, 0, 0, 33587520, 0),
(@NPC_GUID_START + 139, 40004, 645, 3, 1, 33009, 0, 261.859, 793.297, 95.9091, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 140, 40004, 645, 3, 1, 33009, 0, 272.821, 771.333, 95.4186, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 141, 40004, 645, 3, 1, 33009, 0, 277.281, 782.677, 95.9503, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 142, 40004, 645, 3, 1, 33009, 0, 199.877, 764.911, 95.9503, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 143, 40084, 645, 3, 1, 763, 0, 200.955, 824.604, 95.9794, 1.53589, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 144, 40084, 645, 3, 1, 763, 0, 214.299, 833.705, 95.9151, 1.76278, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 145, 40084, 645, 3, 1, 763, 0, 188.431, 800.047, 95.9794, 2.33874, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 146, 40004, 645, 3, 1, 33009, 0, 212.734, 812.198, 95.3666, 0, 120, 0, 0, 123804, 0, 0, 0, 33587520, 0),
(@NPC_GUID_START + 147, 40004, 645, 3, 1, 33009, 0, 213.04, 781.936, 95.9091, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 148, 40004, 645, 3, 1, 33009, 0, 200.438, 779.964, 95.3678, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 149, 40004, 645, 3, 1, 33009, 0, 219.37, 767.696, 95.9091, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 150, 40004, 645, 3, 1, 33009, 0, 196.686, 793.016, 95.9503, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 151, 40084, 645, 3, 1, 763, 0, 251.901, 842.175, 95.8735, 0.20944, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 152, 40004, 645, 3, 1, 33009, 0, 251.564, 821.403, 95.9504, 5.96132, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 153, 39994, 645, 3, 1, 12231, 0, 216.857, 760.341, 95.3489, 5.43449, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 154, 40004, 645, 3, 1, 33009, 0, 229.591, 797.643, 95.9091, 2.74807, 120, 0, 0, 123804, 0, 0, 0, 33587520, 0),
(@NPC_GUID_START + 155, 40084, 645, 3, 1, 763, 0, 190.786, 769.087, 95.9504, 2.68781, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 156, 40084, 645, 3, 1, 763, 0, 295.003, 783.471, 95.9489, 0.610865, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 157, 40004, 645, 3, 1, 33009, 0, 263.707, 775.263, 95.6162, 2.83899, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 158, 40004, 645, 3, 1, 33009, 0, 270.655, 760.335, 95.9503, 0, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 159, 40084, 645, 3, 1, 763, 0, 253.545, 839.882, 95.8857, 1.11701, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 160, 40004, 645, 3, 1, 33009, 0, 246.045, 807.186, 95.9092, 5.62356, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 161, 40084, 645, 3, 1, 763, 0, 198.236, 753.965, 95.9504, 4.86947, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 162, 40084, 645, 3, 1, 763, 0, 299.337, 779.83, 95.949, 1.72788, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 163, 51340, 645, 3, 1, 37285, 0, 289.391, 844.403, 96.007, 3.97935, 120, 0, 0, 64496, 0, 0, 67110912, 0, 0),
(@NPC_GUID_START + 164, 40004, 645, 3, 1, 33009, 0, 248.528, 792.911, 95.9091, 0.722881, 120, 0, 0, 123804, 0, 0, 0, 33849664, 0),
(@NPC_GUID_START + 165, 40021, 645, 3, 1, 35014, 0, 225.809, 711.488, 108.548, 0, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 166, 40021, 645, 3, 1, 35014, 0, 225.773, 707.054, 109.372, 0, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 167, 40019, 645, 3, 1, 34102, 0, 223.201, 717.325, 107.211, 0, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 168, 40021, 645, 3, 1, 35014, 0, 194.399, 697.573, 106.858, 3.4383, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 169, 40343, 645, 3, 1, 11686, 0, 236.637, 706.332, 144.372, 1.66261, 120, 0, 0, 37187, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 170, 40019, 645, 3, 1, 34102, 0, 197.502, 707.972, 108.426, 3.28122, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 171, 40021, 645, 3, 1, 35014, 0, 194.438, 702.007, 108.236, 3.19395, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 172, 40343, 645, 3, 1, 11686, 0, 240.698, 705.167, 116.932, 1.53856, 120, 0, 0, 37187, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 173, 40084, 645, 3, 1, 763, 0, 190.335, 774, 95.9504, 3.49066, 120, 0, 0, 30951, 0, 0, 2048, 32768, 0),
(@NPC_GUID_START + 174, 40019, 645, 3, 1, 34103, 0, 223.049, 702.068, 106.687, 0, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 175, 40023, 645, 3, 1, 36757, 0, 218.918, 672.48, 96.1521, 1.9001, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 176, 40343, 645, 3, 1, 11686, 0, 188.029, 677.277, 112.757, 4.93221, 120, 0, 0, 37187, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 177, 39700, 645, 3, 1, 34433, 0, 102.858, 583.955, 76.7866, 6.14356, 120, 0, 0, 893580, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 178, 40019, 645, 3, 1, 34103, 0, 206.526, 624.354, 79.6383, 3.35103, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 179, 40021, 645, 3, 1, 35014, 0, 202.069, 628.866, 81.5625, 3.4383, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 180, 40343, 645, 3, 1, 11686, 0, 174.663, 651.768, 104.154, 4.83033, 120, 0, 0, 37187, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 181, 39705, 645, 3, 1, 36465, 0, 331.71, 554.49, 66.0065, 3.14159, 120, 0, 0, 837731, 0, 0, 2048, 295744, 0),
(@NPC_GUID_START + 182, 40817, 645, 3, 1, 35979, 0, 331.627, 563.557, 66.0065, 3.14159, 120, 0, 0, 44679, 0, 0, 2048, 295680, 0),
(@NPC_GUID_START + 183, 40023, 645, 3, 1, 36757, 0, 213.555, 663.773, 92.7098, 5.03224, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 184, 40343, 645, 3, 1, 11686, 0, 176.752, 636.551, 112.362, 5.10452, 120, 0, 0, 37187, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 185, 40021, 645, 3, 1, 35014, 0, 202.108, 633.3, 82.9558, 3.19395, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 186, 40019, 645, 3, 1, 34103, 0, 205.109, 639.257, 84.4595, 3.28122, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 187, 40019, 645, 3, 1, 34103, 0, 197.345, 692.719, 103.969, 3.35103, 120, 0, 0, 0, 0, 0, 2048, 32832, 13),
(@NPC_GUID_START + 188, 40017, 645, 3, 1, 34105, 0, 176.722, 576.628, 76.1775, 2.86234, 120, 0, 0, 123804, 39940, 0, 2049, 570721088, 32),
(@NPC_GUID_START + 189, 40017, 645, 3, 1, 34104, 0, 245.099, 576.95, 73.5015, 1.16937, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 190, 40021, 645, 3, 1, 35014, 0, 235.51, 590.896, 75.3419, 4.4855, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 191, 40019, 645, 3, 1, 34103, 0, 238.033, 582.009, 74.7118, 1.18682, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 192, 40017, 645, 3, 1, 34105, 0, 249.34, 583.236, 73.4674, 3.59538, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 193, 40019, 645, 3, 1, 34103, 0, 234.78, 584.002, 74.7178, 1.3439, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 194, 40817, 645, 3, 1, 35979, 0, 332.236, 544.75, 66.0065, 3.14159, 120, 0, 0, 44679, 0, 0, 2048, 295680, 0),
(@NPC_GUID_START + 195, 40017, 645, 3, 1, 34104, 0, 184.266, 587.561, 76.1095, 3.35103, 120, 0, 0, 123804, 39940, 0, 2049, 570721088, 32),
(@NPC_GUID_START + 196, 40023, 645, 3, 1, 36757, 0, 260.692, 556.521, 71.7622, 5.85062, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 197, 40017, 645, 3, 1, 34104, 0, 137.161, 576.28, 76.3806, 1.41372, 120, 0, 0, 123804, 39940, 0, 2049, 570721088, 32),
(@NPC_GUID_START + 198, 40017, 645, 3, 1, 34105, 0, 131.934, 591.681, 76.3988, 3.10669, 120, 0, 0, 123804, 39940, 0, 2049, 570721088, 32),
(@NPC_GUID_START + 199, 40017, 645, 3, 1, 34104, 0, 155.326, 584.078, 76.9742, 5.41052, 120, 0, 0, 123804, 39940, 0, 2049, 570721088, 32),
(@NPC_GUID_START + 200, 40343, 645, 3, 1, 11686, 0, 176.635, 715.721, 121.12, 4.63831, 120, 0, 0, 37187, 0, 0, 2048, 33554432, 0),
(@NPC_GUID_START + 201, 40011, 645, 3, 1, 31701, 0, 122.785, 578.594, 76.433, 5.71001, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 202, 40008, 645, 3, 1, 31701, 0, 116.063, 567.372, 76.4508, 2.62535, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 203, 40021, 645, 3, 1, 35014, 0, 266.392, 550.042, 70.596, 4.53786, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 204, 40019, 645, 3, 1, 34103, 0, 262.689, 549.507, 71.3068, 4.97419, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 205, 40019, 645, 3, 1, 34103, 0, 258.967, 542.038, 71.9529, 0.558505, 120, 0, 0, 123804, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 206, 40023, 645, 3, 1, 36757, 0, 254.617, 564.662, 71.8462, 3.32276, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 207, 40017, 645, 3, 1, 34104, 0, 268.595, 538.292, 70.0541, 2.16421, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 208, 40017, 645, 3, 1, 34104, 0, 271.09, 544.408, 69.632, 3.35103, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 209, 40013, 645, 3, 1, 31701, 0, 121.145, 594.614, 76.2146, 0.774797, 120, 0, 0, 297496, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 210, 40015, 645, 3, 1, 31541, 0, 81.9104, 613.548, 77.0809, 2.46523, 120, 0, 0, 237997, 0, 0, 2048, 32832, 0),
(@NPC_GUID_START + 211, 40017, 645, 3, 1, 34105, 0, 327.151, 541.146, 66.0613, 1.18682, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 212, 40017, 645, 3, 1, 34105, 0, 334.802, 585.045, 66.0065, 0.733038, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0),
(@NPC_GUID_START + 213, 40017, 645, 3, 1, 34105, 0, 344.859, 563.111, 66.0065, 3.75246, 120, 0, 0, 123804, 39940, 0, 2048, 32832, 0);