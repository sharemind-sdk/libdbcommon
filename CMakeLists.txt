#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#

CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(SharemindLibDbCommon VERSION 0.1.2 LANGUAGES CXX)

INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/config.local" OPTIONAL)
INCLUDE("${CMAKE_CURRENT_BINARY_DIR}/config.local" OPTIONAL)

FIND_PACKAGE(SharemindCMakeHelpers 1.6 REQUIRED)


# Headers:
FILE(GLOB_RECURSE SharemindLibDbCommon_HEADERS
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
ADD_CUSTOM_TARGET("include_SharemindLibDbCommon_HEADERS_in_IDE"
                  SOURCES ${SharemindLibDbCommon_HEADERS})
SharemindAddInterfaceLibrary(LibDbCommon)
TARGET_INCLUDE_DIRECTORIES(LibDbCommon
    INTERFACE
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src> # TODO
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)
TARGET_COMPILE_DEFINITIONS(LibDbCommon INTERFACE "__STDC_LIMIT_MACROS")
INSTALL(FILES ${SharemindLibDbCommon_HEADERS}
        DESTINATION "include/sharemind/dbcommon"
        COMPONENT "dev")
SharemindCreateCMakeFindFilesForTarget(LibDbCommon)


# Packaging:
SharemindSetupPackaging()
SharemindAddComponentPackage("dev"
    NAME "libsharemind-dbcommon-dev"
    DESCRIPTION "Sharemind DB common library development headers"
    DEB_SECTION "libdevel"
)
SharemindPackagingFinalize()
