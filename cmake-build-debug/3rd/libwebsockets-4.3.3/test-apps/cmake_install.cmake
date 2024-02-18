# Install script for directory: /Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xexamplesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/wsServer"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/gfc"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/usr/local/mysql-8.0.19-macos10.15-x86_64/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/opt/local/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xexamplesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/libwebsockets-test-server-extpoll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server-extpoll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server-extpoll")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/wsServer"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server-extpoll")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/gfc"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server-extpoll")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server-extpoll")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server-extpoll")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/usr/local/mysql-8.0.19-macos10.15-x86_64/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server-extpoll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/opt/local/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-server-extpoll")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xexamplesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/libwebsockets-test-lejp")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-lejp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-lejp")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/wsServer"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-lejp")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/gfc"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-lejp")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-lejp")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-lejp")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/usr/local/mysql-8.0.19-macos10.15-x86_64/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-lejp")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/opt/local/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-lejp")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xexamplesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/bin/libwebsockets-test-client")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-client" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-client")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/wsServer"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-client")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/gfc"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-client")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/json-c-json-c-0.16-20220414"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-client")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-client")
    execute_process(COMMAND /Users/christian/anaconda3/bin/install_name_tool
      -delete_rpath "/usr/local/mysql-8.0.19-macos10.15-x86_64/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-client")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/opt/local/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libwebsockets-test-client")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xexamplesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/libwebsockets-test-server" TYPE FILE FILES
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/libwebsockets-test-server.key.pem"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/cmake-build-debug/3rd/libwebsockets-4.3.3/libwebsockets-test-server.pem"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/favicon.ico"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/leaf.jpg"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/candide.zip"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/candide-uncompressed.zip"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/libwebsockets.org-logo.svg"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/http2.png"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/wss-over-h2.png"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/lws-common.js"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/test.html"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/test.css"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/test.js"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xexamplesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/libwebsockets-test-server/private" TYPE FILE FILES "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/private/index.html")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xexamplesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/libwebsockets-test-server" TYPE FILE FILES
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/lws-ssh-test-keys"
    "/Volumes/EXPORT/local/works/doublegsoft.net/gim/03.Development/gim/3rd/libwebsockets-4.3.3/test-apps/lws-ssh-test-keys.pub"
    )
endif()

