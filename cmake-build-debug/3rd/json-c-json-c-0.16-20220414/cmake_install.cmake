# Install script for directory: /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS)
  set(CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS "OWNER_READ;OWNER_WRITE;OWNER_EXECUTE;GROUP_READ;GROUP_EXECUTE;WORLD_READ;WORLD_EXECUTE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/libjson-c.5.2.0.dylib"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/libjson-c.5.dylib"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.5.2.0.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.5.dylib"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      execute_process(COMMAND "/Users/christian/anaconda3/bin/install_name_tool"
        -id "libjson-c.5.dylib"
        "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/opt/local/bin/strip" -x "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/libjson-c.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.dylib")
    execute_process(COMMAND "/Users/christian/anaconda3/bin/install_name_tool"
      -id "libjson-c.5.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/opt/local/bin/strip" -x "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/libjson-c.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.a")
    execute_process(COMMAND "/opt/local/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libjson-c.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c/json-c-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c/json-c-targets.cmake"
         "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/CMakeFiles/Export/lib/cmake/json-c/json-c-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c/json-c-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c/json-c-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c" TYPE FILE FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/CMakeFiles/Export/lib/cmake/json-c/json-c-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c" TYPE FILE FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/CMakeFiles/Export/lib/cmake/json-c/json-c-targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/json-c" TYPE FILE FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/json-c-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/json-c.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/json-c/json_config.h;/usr/local/include/json-c/json.h;/usr/local/include/json-c/arraylist.h;/usr/local/include/json-c/debug.h;/usr/local/include/json-c/json_c_version.h;/usr/local/include/json-c/json_inttypes.h;/usr/local/include/json-c/json_object.h;/usr/local/include/json-c/json_object_iterator.h;/usr/local/include/json-c/json_tokener.h;/usr/local/include/json-c/json_types.h;/usr/local/include/json-c/json_util.h;/usr/local/include/json-c/json_visit.h;/usr/local/include/json-c/linkhash.h;/usr/local/include/json-c/printbuf.h;/usr/local/include/json-c/json_pointer.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/json-c" TYPE FILE FILES
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/json_config.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/json.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/arraylist.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/debug.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/json_c_version.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/json_inttypes.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/json_object.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/json_object_iterator.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/json_tokener.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/json_types.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/json_util.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/json_visit.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/linkhash.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/printbuf.h"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/json-c-json-c-0.16-20220414/json_pointer.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/apps/cmake_install.cmake")
  include("/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414/doc/cmake_install.cmake")

endif()

