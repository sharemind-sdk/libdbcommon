#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
PROJECT(SHAREMIND_DBCOMMON)

ADD_COMPILE_OPTIONS(
  "-std=c++11" "-Wall" "-Wextra" "-O2" "-fPIC"
  "$<$<NOT:$<STREQUAL:$<CONFIGURATION>,Release>>:-ggdb>"
  "$<$<NOT:$<STREQUAL:$<CONFIGURATION>,Release>>:-fno-omit-frame-pointer>"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-DNDEBUG>"
  "$<$<STREQUAL:$<CONFIGURATION>,Release>:-fomit-frame-pointer>"
)

FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(LogHard REQUIRED)
FIND_PACKAGE(SharemindCxxHeaders REQUIRED)
FIND_PACKAGE(SharemindLibmodapi REQUIRED)
FIND_PACKAGE(SharemindLibvm REQUIRED)
FIND_PACKAGE(SharemindVmGlobals REQUIRED)

INCLUDE_DIRECTORIES(
    ${Boost_INCLUDE_DIRS}
    ${LogHard_INCLUDE_DIRS}
    ${SharemindCxxHeaders_INCLUDE_DIRS}
    ${SharemindLibmodapi_INCLUDE_DIRS}
    ${SharemindLibvm_INCLUDE_DIRS}
    ${SharemindVmGlobals_INCLUDE_DIRS}
)
INCLUDE_DIRECTORIES(BEFORE "${CMAKE_CURRENT_SOURCE_DIR}/../../")

ADD_DEFINITIONS(
    "-D__STDC_LIMIT_MACROS"
    ${LogHard_DEFINITIONS}
    ${SharemindCxxHeaders_DEFINITIONS}
    ${SharemindLibmodapi_DEFINITIONS}
    ${SharemindLibvm_DEFINITIONS}
    ${SharemindVmGlobals_DEFINITIONS}
)

SET(DBCOMMON_EXTERNAL_LIBS
    ${LogHard_LIBRARIES}
    ${SharemindCxxHeaders_LIBRARIES}
    ${SharemindLibmodapi_LIBRARIES}
    ${SharemindLibvm_LIBRARIES}
    ${SharemindVmGlobals_LIBRARIES}
)

SET(DBCOMMON_SOURCES
    DataSource.cpp
    DataSourceManager.cpp
)

SET(DBCOMMON_HEADERS
    DataSource.h
    DataSourceManager.h
    datasourceapi.h
    ModuleLoader.h
)

IF(NOT SHAREMIND_DBCOMMON_LINKING_MODE)
    SET(SHAREMIND_DBCOMMON_LINKING_MODE STATIC)
ENDIF()
ADD_LIBRARY(sharemind_dbcommon ${SHAREMIND_DBCOMMON_LINKING_MODE} ${DBCOMMON_SOURCES} ${DBCOMMON_HEADERS})
TARGET_LINK_LIBRARIES(sharemind_dbcommon ${DBCOMMON_EXTERNAL_LIBS})

INSTALL(TARGETS sharemind_dbcommon
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib")
INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
        DESTINATION "include/sharemind/dbcommon"
        FILES_MATCHING PATTERN "*.h")
