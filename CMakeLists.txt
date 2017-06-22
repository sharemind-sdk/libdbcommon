#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(SHAREMIND_LIBDBCOMMON)
SET(SHAREMIND_LIBDBCOMMON_VERSION "0.1.0")

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        DESTINATION "include/sharemind/dbcommon"
        FILES_MATCHING PATTERN "*.h")

SET(SHAREMIND_LIBDBCOMMON_INSTALL_INCLUDE_DIRS
    "${CMAKE_INSTALL_PREFIX}/include")
SET(SHAREMIND_LIBDBCOMMON_INSTALL_DEFINITIONS "-D__STDC_LIMIT_MACROS")
SET(SHAREMIND_LIBDBCOMMON_INSTALL_LIBRARIES "")
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibDbCommonConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibDbCommonConfig.cmake" @ONLY)
INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibDbCommonConfig.cmake"
        DESTINATION "lib/SharemindLibDbCommon")
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/SharemindLibDbCommonConfigVersion.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibDbCommonConfigVersion.cmake" @ONLY)
INSTALL(FILES "${CMAKE_CURRENT_BINARY_DIR}/SharemindLibDbCommonConfigVersion.cmake"
        DESTINATION "lib/SharemindLibDbCommon")
