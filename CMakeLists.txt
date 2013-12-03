#
# This file is a part of the Sharemind framework.
# Copyright (C) Cybernetica AS
#
# All rights are reserved. Reproduction in whole or part is prohibited
# without the written consent of the copyright owner. The usage of this
# code is subject to the appropriate license agreement.
#

# The dbcommon library


# Find required libraries:
#SET(Boost_USE_STATIC_RUNTIME OFF)

INCLUDE_DIRECTORIES(
    ${Boost_INCLUDE_DIRS}
)


# Set the default log level and reconfigure headers accordingly.
# Possible values: WARNING, NORMAL, DEBUG, FULLDEBUG.
ADD_DEFINITIONS("-DSHAREMIND_LOGLEVEL_${LOGLEVEL}" "-D__STDC_LIMIT_MACROS")


SET(DBCOMMON_SOURCES
    ModuleLoader/LastError.cpp
    ModuleLoader/ModuleLoader.cpp
    ModuleLoader/Modules.cpp
    DataSource.cpp
    DataSourceManager.cpp
)

SET(DBCOMMON_HEADERS
    ModuleLoader/LastError.h
    ModuleLoader/ModuleLoader.h
    ModuleLoader/Modules.h
    DataSource.h
    DataSourceManager.h
    datasourceapi.h
)

# compile the library
IF(NOT SHAREMIND_DBCOMMON_LINKING_MODE)
    SET(SHAREMIND_DBCOMMON_LINKING_MODE STATIC)
ENDIF()

ADD_LIBRARY(sharemind_dbcommon ${SHAREMIND_DBCOMMON_LINKING_MODE} ${DBCOMMON_SOURCES} ${DBCOMMON_HEADERS})
SET_TARGET_PROPERTIES(sharemind_dbcommon PROPERTIES
                      COMPILE_FLAGS "-fPIC -O2 -ggdb")

MACRO(SHAREMIND_DBCOMMON_TARGETLIB libname)
  IF(TARGET "lib${libname}")
    SET(SHAREMIND_DBCOMMON_TARGETLIB_${libname} "lib${libname}")
  ELSE()
    SET(SHAREMIND_DBCOMMON_TARGETLIB_${libname} "-L${CMAKE_PREFIX_PATH}/lib" "sharemind_${libname}")
  ENDIF()
ENDMACRO()
SHAREMIND_DBCOMMON_TARGETLIB(modapi)

# use these libraries during linking
TARGET_LINK_LIBRARIES(sharemind_dbcommon
    ${SHAREMIND_DBCOMMON_TARGETLIB_modapi}
)

# Install the library and headers
#INSTALL(TARGETS sharemind_dbcommon
#        ARCHIVE DESTINATION "lib")
#
#INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
#        DESTINATION "include/sharemind/dbcommon"
#        FILES_MATCHING PATTERN "*.h")
