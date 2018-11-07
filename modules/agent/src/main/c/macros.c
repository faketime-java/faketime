#define concat(a, b) a##b

#define generateFakeMethod(methodIndex) jobject JNICALL \
concat(fakeMethod, methodIndex)(JNIEnv *jni_env, jobject object, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7, void *arg8, void *arg9, void *arg10) { \
  if (currentTimeMillisMethodIndex == methodIndex) { \
    return fakeCurrentTimeMillisReturningObject(jni_env, object); \
  } else if (getNanoTimeAdjustmentMethodIndex == methodIndex) { \
    return fakeGetNanoTimeAdjustmentReturningObject(jni_env, object, (jlong)arg1); \
  } \
  \
  return realMethods[methodIndex](jni_env, object, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10); \
}

#define generateFakeMethodCase(methodIndex) \
case methodIndex: \
  realMethods[methodIndex] = address; \
  *new_address_ptr = concat(&fakeMethod, methodIndex); \
  break;

#define generateFakeMethods \
generateFakeMethod(0) \
generateFakeMethod(1) \
generateFakeMethod(2) \
generateFakeMethod(3) \
generateFakeMethod(4) \
generateFakeMethod(5) \
generateFakeMethod(6) \
generateFakeMethod(7) \
generateFakeMethod(8) \
generateFakeMethod(9) \
generateFakeMethod(10) \
generateFakeMethod(11) \
generateFakeMethod(12) \
generateFakeMethod(13) \
generateFakeMethod(14) \
generateFakeMethod(15) \
generateFakeMethod(16) \
generateFakeMethod(17) \
generateFakeMethod(18) \
generateFakeMethod(19) \
generateFakeMethod(20) \
generateFakeMethod(21) \
generateFakeMethod(22) \
generateFakeMethod(23) \
generateFakeMethod(24) \
generateFakeMethod(25) \
generateFakeMethod(26) \
generateFakeMethod(27) \
generateFakeMethod(28) \
generateFakeMethod(29) \
generateFakeMethod(30) \
generateFakeMethod(31) \
generateFakeMethod(32) \
generateFakeMethod(33) \
generateFakeMethod(34) \
generateFakeMethod(35) \
generateFakeMethod(36) \
generateFakeMethod(37) \
generateFakeMethod(38) \
generateFakeMethod(39) \
generateFakeMethod(40) \
generateFakeMethod(41) \
generateFakeMethod(42) \
generateFakeMethod(43) \
generateFakeMethod(44) \
generateFakeMethod(45) \
generateFakeMethod(46) \
generateFakeMethod(47) \
generateFakeMethod(48) \
generateFakeMethod(49) \
generateFakeMethod(50) \
generateFakeMethod(51) \
generateFakeMethod(52) \
generateFakeMethod(53) \
generateFakeMethod(54) \
generateFakeMethod(55) \
generateFakeMethod(56) \
generateFakeMethod(57) \
generateFakeMethod(58) \
generateFakeMethod(59) \
generateFakeMethod(60) \
generateFakeMethod(61) \
generateFakeMethod(62) \
generateFakeMethod(63) \
generateFakeMethod(64) \
generateFakeMethod(65) \
generateFakeMethod(66) \
generateFakeMethod(67) \
generateFakeMethod(68) \
generateFakeMethod(69) \
generateFakeMethod(70) \
generateFakeMethod(71) \
generateFakeMethod(72) \
generateFakeMethod(73) \
generateFakeMethod(74) \
generateFakeMethod(75) \
generateFakeMethod(76) \
generateFakeMethod(77) \
generateFakeMethod(78) \
generateFakeMethod(79) \
generateFakeMethod(80) \
generateFakeMethod(81) \
generateFakeMethod(82) \
generateFakeMethod(83) \
generateFakeMethod(84) \
generateFakeMethod(85) \
generateFakeMethod(86) \
generateFakeMethod(87) \
generateFakeMethod(88) \
generateFakeMethod(89) \
generateFakeMethod(90) \
generateFakeMethod(91) \
generateFakeMethod(92) \
generateFakeMethod(93) \
generateFakeMethod(94) \
generateFakeMethod(95) \
generateFakeMethod(96) \
generateFakeMethod(97) \
generateFakeMethod(98) \
generateFakeMethod(99) \
generateFakeMethod(100) \
generateFakeMethod(101) \
generateFakeMethod(102) \
generateFakeMethod(103) \
generateFakeMethod(104) \
generateFakeMethod(105) \
generateFakeMethod(106) \
generateFakeMethod(107) \
generateFakeMethod(108) \
generateFakeMethod(109) \
generateFakeMethod(110) \
generateFakeMethod(111) \
generateFakeMethod(112) \
generateFakeMethod(113) \
generateFakeMethod(114) \
generateFakeMethod(115) \
generateFakeMethod(116) \
generateFakeMethod(117) \
generateFakeMethod(118) \
generateFakeMethod(119) \
generateFakeMethod(120) \
generateFakeMethod(121) \
generateFakeMethod(122) \
generateFakeMethod(123) \
generateFakeMethod(124) \
generateFakeMethod(125) \
generateFakeMethod(126) \
generateFakeMethod(127) \
generateFakeMethod(128) \
generateFakeMethod(129) \
generateFakeMethod(130) \
generateFakeMethod(131) \
generateFakeMethod(132) \
generateFakeMethod(133) \
generateFakeMethod(134) \
generateFakeMethod(135) \
generateFakeMethod(136) \
generateFakeMethod(137) \
generateFakeMethod(138) \
generateFakeMethod(139) \
generateFakeMethod(140) \
generateFakeMethod(141) \
generateFakeMethod(142) \
generateFakeMethod(143) \
generateFakeMethod(144) \
generateFakeMethod(145) \
generateFakeMethod(146) \
generateFakeMethod(147) \
generateFakeMethod(148) \
generateFakeMethod(149) \
generateFakeMethod(150) \
generateFakeMethod(151) \
generateFakeMethod(152) \
generateFakeMethod(153) \
generateFakeMethod(154) \
generateFakeMethod(155) \
generateFakeMethod(156) \
generateFakeMethod(157) \
generateFakeMethod(158) \
generateFakeMethod(159) \
generateFakeMethod(160) \
generateFakeMethod(161) \
generateFakeMethod(162) \
generateFakeMethod(163) \
generateFakeMethod(164) \
generateFakeMethod(165) \
generateFakeMethod(166) \
generateFakeMethod(167) \
generateFakeMethod(168) \
generateFakeMethod(169) \
generateFakeMethod(170) \
generateFakeMethod(171) \
generateFakeMethod(172) \
generateFakeMethod(173) \
generateFakeMethod(174) \
generateFakeMethod(175) \
generateFakeMethod(176) \
generateFakeMethod(177) \
generateFakeMethod(178) \
generateFakeMethod(179) \
generateFakeMethod(180) \
generateFakeMethod(181) \
generateFakeMethod(182) \
generateFakeMethod(183) \
generateFakeMethod(184) \
generateFakeMethod(185) \
generateFakeMethod(186) \
generateFakeMethod(187) \
generateFakeMethod(188) \
generateFakeMethod(189) \
generateFakeMethod(190) \
generateFakeMethod(191) \
generateFakeMethod(192) \
generateFakeMethod(193) \
generateFakeMethod(194) \
generateFakeMethod(195) \
generateFakeMethod(196) \
generateFakeMethod(197) \
generateFakeMethod(198) \
generateFakeMethod(199) \
generateFakeMethod(200) \
generateFakeMethod(201) \
generateFakeMethod(202) \
generateFakeMethod(203) \
generateFakeMethod(204) \
generateFakeMethod(205) \
generateFakeMethod(206) \
generateFakeMethod(207) \
generateFakeMethod(208) \
generateFakeMethod(209) \
generateFakeMethod(210) \
generateFakeMethod(211) \
generateFakeMethod(212) \
generateFakeMethod(213) \
generateFakeMethod(214) \
generateFakeMethod(215) \
generateFakeMethod(216) \
generateFakeMethod(217) \
generateFakeMethod(218) \
generateFakeMethod(219) \
generateFakeMethod(220) \
generateFakeMethod(221) \
generateFakeMethod(222) \
generateFakeMethod(223) \
generateFakeMethod(224) \
generateFakeMethod(225) \
generateFakeMethod(226) \
generateFakeMethod(227) \
generateFakeMethod(228) \
generateFakeMethod(229) \
generateFakeMethod(230) \
generateFakeMethod(231) \
generateFakeMethod(232) \
generateFakeMethod(233) \
generateFakeMethod(234) \
generateFakeMethod(235) \
generateFakeMethod(236) \
generateFakeMethod(237) \
generateFakeMethod(238) \
generateFakeMethod(239) \
generateFakeMethod(240) \
generateFakeMethod(241) \
generateFakeMethod(242) \
generateFakeMethod(243) \
generateFakeMethod(244) \
generateFakeMethod(245) \
generateFakeMethod(246) \
generateFakeMethod(247) \
generateFakeMethod(248) \
generateFakeMethod(249) \
generateFakeMethod(250) \
generateFakeMethod(251) \
generateFakeMethod(252) \
generateFakeMethod(253) \
generateFakeMethod(254) \
generateFakeMethod(255) \
generateFakeMethod(256) \
generateFakeMethod(257) \
generateFakeMethod(258) \
generateFakeMethod(259) \
generateFakeMethod(260) \
generateFakeMethod(261) \
generateFakeMethod(262) \
generateFakeMethod(263) \
generateFakeMethod(264) \
generateFakeMethod(265) \
generateFakeMethod(266) \
generateFakeMethod(267) \
generateFakeMethod(268) \
generateFakeMethod(269) \
generateFakeMethod(270) \
generateFakeMethod(271) \
generateFakeMethod(272) \
generateFakeMethod(273) \
generateFakeMethod(274) \
generateFakeMethod(275) \
generateFakeMethod(276) \
generateFakeMethod(277) \
generateFakeMethod(278) \
generateFakeMethod(279) \
generateFakeMethod(280) \
generateFakeMethod(281) \
generateFakeMethod(282) \
generateFakeMethod(283) \
generateFakeMethod(284) \
generateFakeMethod(285) \
generateFakeMethod(286) \
generateFakeMethod(287) \
generateFakeMethod(288) \
generateFakeMethod(289) \
generateFakeMethod(290) \
generateFakeMethod(291) \
generateFakeMethod(292) \
generateFakeMethod(293) \
generateFakeMethod(294) \
generateFakeMethod(295) \
generateFakeMethod(296) \
generateFakeMethod(297) \
generateFakeMethod(298) \
generateFakeMethod(299) \
generateFakeMethod(300)

#define generateFakeMethodCases \
generateFakeMethodCase(0) \
generateFakeMethodCase(1) \
generateFakeMethodCase(2) \
generateFakeMethodCase(3) \
generateFakeMethodCase(4) \
generateFakeMethodCase(5) \
generateFakeMethodCase(6) \
generateFakeMethodCase(7) \
generateFakeMethodCase(8) \
generateFakeMethodCase(9) \
generateFakeMethodCase(10) \
generateFakeMethodCase(11) \
generateFakeMethodCase(12) \
generateFakeMethodCase(13) \
generateFakeMethodCase(14) \
generateFakeMethodCase(15) \
generateFakeMethodCase(16) \
generateFakeMethodCase(17) \
generateFakeMethodCase(18) \
generateFakeMethodCase(19) \
generateFakeMethodCase(20) \
generateFakeMethodCase(21) \
generateFakeMethodCase(22) \
generateFakeMethodCase(23) \
generateFakeMethodCase(24) \
generateFakeMethodCase(25) \
generateFakeMethodCase(26) \
generateFakeMethodCase(27) \
generateFakeMethodCase(28) \
generateFakeMethodCase(29) \
generateFakeMethodCase(30) \
generateFakeMethodCase(31) \
generateFakeMethodCase(32) \
generateFakeMethodCase(33) \
generateFakeMethodCase(34) \
generateFakeMethodCase(35) \
generateFakeMethodCase(36) \
generateFakeMethodCase(37) \
generateFakeMethodCase(38) \
generateFakeMethodCase(39) \
generateFakeMethodCase(40) \
generateFakeMethodCase(41) \
generateFakeMethodCase(42) \
generateFakeMethodCase(43) \
generateFakeMethodCase(44) \
generateFakeMethodCase(45) \
generateFakeMethodCase(46) \
generateFakeMethodCase(47) \
generateFakeMethodCase(48) \
generateFakeMethodCase(49) \
generateFakeMethodCase(50) \
generateFakeMethodCase(51) \
generateFakeMethodCase(52) \
generateFakeMethodCase(53) \
generateFakeMethodCase(54) \
generateFakeMethodCase(55) \
generateFakeMethodCase(56) \
generateFakeMethodCase(57) \
generateFakeMethodCase(58) \
generateFakeMethodCase(59) \
generateFakeMethodCase(60) \
generateFakeMethodCase(61) \
generateFakeMethodCase(62) \
generateFakeMethodCase(63) \
generateFakeMethodCase(64) \
generateFakeMethodCase(65) \
generateFakeMethodCase(66) \
generateFakeMethodCase(67) \
generateFakeMethodCase(68) \
generateFakeMethodCase(69) \
generateFakeMethodCase(70) \
generateFakeMethodCase(71) \
generateFakeMethodCase(72) \
generateFakeMethodCase(73) \
generateFakeMethodCase(74) \
generateFakeMethodCase(75) \
generateFakeMethodCase(76) \
generateFakeMethodCase(77) \
generateFakeMethodCase(78) \
generateFakeMethodCase(79) \
generateFakeMethodCase(80) \
generateFakeMethodCase(81) \
generateFakeMethodCase(82) \
generateFakeMethodCase(83) \
generateFakeMethodCase(84) \
generateFakeMethodCase(85) \
generateFakeMethodCase(86) \
generateFakeMethodCase(87) \
generateFakeMethodCase(88) \
generateFakeMethodCase(89) \
generateFakeMethodCase(90) \
generateFakeMethodCase(91) \
generateFakeMethodCase(92) \
generateFakeMethodCase(93) \
generateFakeMethodCase(94) \
generateFakeMethodCase(95) \
generateFakeMethodCase(96) \
generateFakeMethodCase(97) \
generateFakeMethodCase(98) \
generateFakeMethodCase(99) \
generateFakeMethodCase(100) \
generateFakeMethodCase(101) \
generateFakeMethodCase(102) \
generateFakeMethodCase(103) \
generateFakeMethodCase(104) \
generateFakeMethodCase(105) \
generateFakeMethodCase(106) \
generateFakeMethodCase(107) \
generateFakeMethodCase(108) \
generateFakeMethodCase(109) \
generateFakeMethodCase(110) \
generateFakeMethodCase(111) \
generateFakeMethodCase(112) \
generateFakeMethodCase(113) \
generateFakeMethodCase(114) \
generateFakeMethodCase(115) \
generateFakeMethodCase(116) \
generateFakeMethodCase(117) \
generateFakeMethodCase(118) \
generateFakeMethodCase(119) \
generateFakeMethodCase(120) \
generateFakeMethodCase(121) \
generateFakeMethodCase(122) \
generateFakeMethodCase(123) \
generateFakeMethodCase(124) \
generateFakeMethodCase(125) \
generateFakeMethodCase(126) \
generateFakeMethodCase(127) \
generateFakeMethodCase(128) \
generateFakeMethodCase(129) \
generateFakeMethodCase(130) \
generateFakeMethodCase(131) \
generateFakeMethodCase(132) \
generateFakeMethodCase(133) \
generateFakeMethodCase(134) \
generateFakeMethodCase(135) \
generateFakeMethodCase(136) \
generateFakeMethodCase(137) \
generateFakeMethodCase(138) \
generateFakeMethodCase(139) \
generateFakeMethodCase(140) \
generateFakeMethodCase(141) \
generateFakeMethodCase(142) \
generateFakeMethodCase(143) \
generateFakeMethodCase(144) \
generateFakeMethodCase(145) \
generateFakeMethodCase(146) \
generateFakeMethodCase(147) \
generateFakeMethodCase(148) \
generateFakeMethodCase(149) \
generateFakeMethodCase(150) \
generateFakeMethodCase(151) \
generateFakeMethodCase(152) \
generateFakeMethodCase(153) \
generateFakeMethodCase(154) \
generateFakeMethodCase(155) \
generateFakeMethodCase(156) \
generateFakeMethodCase(157) \
generateFakeMethodCase(158) \
generateFakeMethodCase(159) \
generateFakeMethodCase(160) \
generateFakeMethodCase(161) \
generateFakeMethodCase(162) \
generateFakeMethodCase(163) \
generateFakeMethodCase(164) \
generateFakeMethodCase(165) \
generateFakeMethodCase(166) \
generateFakeMethodCase(167) \
generateFakeMethodCase(168) \
generateFakeMethodCase(169) \
generateFakeMethodCase(170) \
generateFakeMethodCase(171) \
generateFakeMethodCase(172) \
generateFakeMethodCase(173) \
generateFakeMethodCase(174) \
generateFakeMethodCase(175) \
generateFakeMethodCase(176) \
generateFakeMethodCase(177) \
generateFakeMethodCase(178) \
generateFakeMethodCase(179) \
generateFakeMethodCase(180) \
generateFakeMethodCase(181) \
generateFakeMethodCase(182) \
generateFakeMethodCase(183) \
generateFakeMethodCase(184) \
generateFakeMethodCase(185) \
generateFakeMethodCase(186) \
generateFakeMethodCase(187) \
generateFakeMethodCase(188) \
generateFakeMethodCase(189) \
generateFakeMethodCase(190) \
generateFakeMethodCase(191) \
generateFakeMethodCase(192) \
generateFakeMethodCase(193) \
generateFakeMethodCase(194) \
generateFakeMethodCase(195) \
generateFakeMethodCase(196) \
generateFakeMethodCase(197) \
generateFakeMethodCase(198) \
generateFakeMethodCase(199) \
generateFakeMethodCase(200) \
generateFakeMethodCase(201) \
generateFakeMethodCase(202) \
generateFakeMethodCase(203) \
generateFakeMethodCase(204) \
generateFakeMethodCase(205) \
generateFakeMethodCase(206) \
generateFakeMethodCase(207) \
generateFakeMethodCase(208) \
generateFakeMethodCase(209) \
generateFakeMethodCase(210) \
generateFakeMethodCase(211) \
generateFakeMethodCase(212) \
generateFakeMethodCase(213) \
generateFakeMethodCase(214) \
generateFakeMethodCase(215) \
generateFakeMethodCase(216) \
generateFakeMethodCase(217) \
generateFakeMethodCase(218) \
generateFakeMethodCase(219) \
generateFakeMethodCase(220) \
generateFakeMethodCase(221) \
generateFakeMethodCase(222) \
generateFakeMethodCase(223) \
generateFakeMethodCase(224) \
generateFakeMethodCase(225) \
generateFakeMethodCase(226) \
generateFakeMethodCase(227) \
generateFakeMethodCase(228) \
generateFakeMethodCase(229) \
generateFakeMethodCase(230) \
generateFakeMethodCase(231) \
generateFakeMethodCase(232) \
generateFakeMethodCase(233) \
generateFakeMethodCase(234) \
generateFakeMethodCase(235) \
generateFakeMethodCase(236) \
generateFakeMethodCase(237) \
generateFakeMethodCase(238) \
generateFakeMethodCase(239) \
generateFakeMethodCase(240) \
generateFakeMethodCase(241) \
generateFakeMethodCase(242) \
generateFakeMethodCase(243) \
generateFakeMethodCase(244) \
generateFakeMethodCase(245) \
generateFakeMethodCase(246) \
generateFakeMethodCase(247) \
generateFakeMethodCase(248) \
generateFakeMethodCase(249) \
generateFakeMethodCase(250) \
generateFakeMethodCase(251) \
generateFakeMethodCase(252) \
generateFakeMethodCase(253) \
generateFakeMethodCase(254) \
generateFakeMethodCase(255) \
generateFakeMethodCase(256) \
generateFakeMethodCase(257) \
generateFakeMethodCase(258) \
generateFakeMethodCase(259) \
generateFakeMethodCase(260) \
generateFakeMethodCase(261) \
generateFakeMethodCase(262) \
generateFakeMethodCase(263) \
generateFakeMethodCase(264) \
generateFakeMethodCase(265) \
generateFakeMethodCase(266) \
generateFakeMethodCase(267) \
generateFakeMethodCase(268) \
generateFakeMethodCase(269) \
generateFakeMethodCase(270) \
generateFakeMethodCase(271) \
generateFakeMethodCase(272) \
generateFakeMethodCase(273) \
generateFakeMethodCase(274) \
generateFakeMethodCase(275) \
generateFakeMethodCase(276) \
generateFakeMethodCase(277) \
generateFakeMethodCase(278) \
generateFakeMethodCase(279) \
generateFakeMethodCase(280) \
generateFakeMethodCase(281) \
generateFakeMethodCase(282) \
generateFakeMethodCase(283) \
generateFakeMethodCase(284) \
generateFakeMethodCase(285) \
generateFakeMethodCase(286) \
generateFakeMethodCase(287) \
generateFakeMethodCase(288) \
generateFakeMethodCase(289) \
generateFakeMethodCase(290) \
generateFakeMethodCase(291) \
generateFakeMethodCase(292) \
generateFakeMethodCase(293) \
generateFakeMethodCase(294) \
generateFakeMethodCase(295) \
generateFakeMethodCase(296) \
generateFakeMethodCase(297) \
generateFakeMethodCase(298) \
generateFakeMethodCase(299) \
generateFakeMethodCase(300)
