##
##              o8o
##              `"'
##   .oooooooo oooo  ooo. .oo.  .oo.
##  888' `88b  `888  `888P"Y88bP"Y88b
##  888   888   888   888   888   888
##  `88bod8P'   888   888   888   888
##  `8oooooo.  o888o o888o o888o o888o
##  d"     YD
##  "Y88888P'
##
cmake_minimum_required(VERSION 3.16)
project(gim C)

set(CMAKE_C_STANDARD 11)
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   set(MYSQL_INCLUDE_DIR       "/usr/local/mysql-8.0.19-macos10.15-x86_64/include")
   set(MYSQL_LIBRARY_DIR       "/usr/local/mysql-8.0.19-macos10.15-x86_64/lib")
#  set(MYSQL_INCLUDE_DIR       "/export/local/opens/mysql-server-8.0.12/build/darwin/include"
#    "/export/local/opens/mysql-server-8.0.12/include"
#    "/export/local/opens/mysql-server-8.0.12/libbinlogevents/export")
#  set(MYSQL_LIBRARY_DIR       "/export/local/opens/mysql-server-8.0.12/build/darwin/lib")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(MYSQL_INCLUDE_DIR       "/usr/include/mysql")
  set(MYSQL_LIBRARY_DIR       "/usr/lib64/mysql")
endif ("设置mysqlclient路径")


set(WS "wsServer")
set(JSON-C                  "json-c-json-c-0.16-20220414")
set(SQLITE                  "sqlite-amalgamation-3.38.2")
set(LIBWEBSOCKETS           "libwebsockets-4.3.3")
set(GFC                     "gfc")

set(UUID                    "")
set(SQLITE3                 "sqlite3")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(UUID                    "uuid")
set(SQLITE3                 "")
endif ("设置uuid库是否需要")

include_directories(
  src
  3rd/${WS}/include
  3rd/${GFC}/include
  ${CMAKE_BINARY_DIR}/3rd/${LIBWEBSOCKETS}
  3rd/${LIBWEBSOCKETS}/include
  ${MYSQL_INCLUDE_DIR}
  3rd/${JSON-C}
  ${CMAKE_BINARY_DIR}/3rd/${JSON-C}
)
link_directories(
  ${CMAKE_BINARY_DIR}/3rd/${WS}
  ${CMAKE_BINARY_DIR}/3rd/${GFC}
  ${CMAKE_BINARY_DIR}/3rd/${JSON-C}
  ${CMAKE_BINARY_DIR}/3rd/${LIBWEBSOCKETS}/lib
  ${MYSQL_LIBRARY_DIR}
)

add_subdirectory(3rd/${WS})
add_subdirectory(3rd/${JSON-C})
#add_subdirectory(3rd/${SQLITE})
#add_subdirectory(3rd/${LIBWEBSOCKETS})

set(WITH_GFC_JVM OFF CACHE BOOL "gfc jvm" FORCE)
set(WITH_GFC_CRYPTO OFF CACHE BOOL "gfc crypto" FORCE)
add_subdirectory(3rd/${GFC})

add_executable(gim
  src/ini.c
  src/gim-util.c
  src/gim-mysql.c
  src/gim-biz.c
  src/gim.c
)

target_link_libraries(gim PRIVATE
  ws
  json-c
  ${CMAKE_BINARY_DIR}/3rd/${GFC}/libgfc.a
#  ${CMAKE_BINARY_DIR}/3rd/${LIBWEBSOCKETS}/libwebsockets.a
  mysqlclient
  ${UUID}
  ${SQLITE3}
)

add_executable(gim_test_error
  test/toyws.c
  test/gim_test_error.c
)

add_executable(gim_test_send
  test/toyws.c
  test/gim_test_send.c
)

add_executable(gim_test_receive
  test/toyws.c
  test/gim_test_receive.c
)

add_executable(gim_test_login
  test/toyws.c
  test/gim_test_login.c
)

add_executable(gim_test_mysql
  src/gim-mysql.c
  src/gim-util.c
  test/gim_test_mysql.c
)

add_executable(gim_test_biz
  src/gim-mysql.c
  src/gim-util.c
  src/gim-biz.c
  test/toyws.c
  test/gim_test_biz.c
)

add_executable(gim_test_10k
  test/toyws.c
  test/gim_test_10k.c
)

target_link_libraries(gim_test_mysql PRIVATE
  gfc
  json-c
  mysqlclient
  ${UUID}
)

target_link_libraries(gim_test_biz PRIVATE
  ws
  gfc
  json-c
  mysqlclient
  ${UUID}
)

add_executable(gim_sender
  test/toyws.c
  test/gim_sender.c
)

add_executable(gim_receiver
  test/toyws.c
  test/gim_receiver.c
)

add_executable(gim_get_messages
  test/toyws.c
  test/gim_get_messages.c
)

add_executable(gim_client
  test/gim_client.c
  test/toyws.c
  src/gim-util.c
)

target_link_libraries(gim_client
  json-c
  ${UUID}
)
