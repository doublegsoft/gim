# - Config file for lws

# It defines the following variables
#  LIBWEBSOCKETS_INCLUDE_DIRS - include directories for lws
#  LIBWEBSOCKETS_LIBRARIES    - libraries to link against

# Get the path of the current file.
get_filename_component(LWS_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
list(APPEND CMAKE_MODULE_PATH ${libwebsockets_DIR})

set(LIBWEBSOCKETS_INCLUDE_DIRS "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/lib;/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3" "/usr/local/Cellar/openssl@3/3.1.3/include")

# Include the project Targets file, this contains definitions for IMPORTED targets.
include(${LWS_CMAKE_DIR}/LibwebsocketsTargets.cmake)
include(${LWS_CMAKE_DIR}/LwsCheckRequirements.cmake)

# IMPORTED targets from LibwebsocketsTargets.cmake
set(LIBWEBSOCKETS_LIBRARIES websockets websockets_shared)

# These are additional include paths you will need
foreach(item "${LIBWEBSOCKETS_INCLUDE_DIRS}")
	include_directories(${item})
	set(CMAKE_REQUIRED_INCLUDES "${CMAKE_REQUIRED_INCLUDES}" ${item})
endforeach()

# These are additional libs that lws wants your app to also link to
foreach(item "-lpthread;m")
	list(APPEND LIBWEBSOCKETS_DEP_LIBS ${item})
endforeach()

# Move boilerplate for consuming cmake files into here

include(CheckIncludeFile)
include(CheckCSourceCompiles)
set(requirements 1)

