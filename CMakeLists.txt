project(shoutjs)
cmake_minimum_required(VERSION 3.17)

set(NODE_INSTALL_DIR $ENV{NODE_INSTALL_DIR})

add_library(shoutjs SHARED src/Shout.cpp)

message(${NODE_INSTALL_DIR})

find_package(PkgConfig)

pkg_check_modules(SHOUT REQUIRED shout)

set(LIBRARIES ${SHOUT_LIBRARIES})
set(INCLUDE_DIRS ${SHOUT_INCLUDE_DIRS})

if(CMAKE_JS_VERSION)
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${CMAKE_JS_INC})
    set(LIBRARIES ${LIBRARIES} ${CMAKE_JS_LIB})
    set_target_properties(shoutjs PROPERTIES PREFIX "" SUFFIX ".node")
else()
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${NODE_INSTALL_DIR}/include/node ${CMAKE_CURRENT_SOURCE_DIR}/node_modules/nan)
endif()

target_include_directories(shoutjs PRIVATE ${INCLUDE_DIRS})
target_link_libraries(shoutjs PRIVATE ${LIBRARIES})
target_compile_options(shoutjs PRIVATE ${SHOUT_CFLAGS_OTHER})
