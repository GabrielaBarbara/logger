###########===> /logger/CMakeLists.txt

cmake_minimum_required(VERSION 2.8)

project(logger)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

    # logging turned on with colour                    
    set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -ggdb -fPIC -DCOLOR_ON=1 -DLOGGING_ON=1")

    # logging turn on without colour
    # set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -ggdb -fPIC -DCOLOR_ON=1 -DLOGGING_ON=1")

    # no logging, no colour
    # set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -ggdb -fPIC -DCOLOR_ON=0 -DLOGGING_ON=0")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

set(INCLUDE_DIR include)
include_directories (${INCLUDE_DIR}) 
add_library (logger_lib src/logger)
add_subdirectory(src)
add_subdirectory(test)
