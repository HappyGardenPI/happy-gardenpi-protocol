cmake_minimum_required(VERSION 3.16)

project(hgardenpi_protocol  VERSION "1.0.1" LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

message(STATUS " start googletest download")
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/hgardenpi-protocol/config.h)

add_library(hgardenpi_protocol
        include/hgardenpi-protocol/packages/aggregation.hpp
        include/hgardenpi-protocol/packages/certificate.hpp
        include/hgardenpi-protocol/packages/error.hpp
        include/hgardenpi-protocol/packages/finish.hpp
        include/hgardenpi-protocol/packages/package.hpp
        include/hgardenpi-protocol/packages/station.hpp
        include/hgardenpi-protocol/packages/synchro.hpp
        include/hgardenpi-protocol/utilities/stringutils.hpp
        include/hgardenpi-protocol/constants.hpp
        include/hgardenpi-protocol/head.hpp
        include/hgardenpi-protocol/protocol.hpp
        src/3thparts/libcrc/crc8.c
        src/3thparts/libcrc/crc16.c
        src/3thparts/libcrc/crcccitt.c
        src/3thparts/libcrc/crcdnp.c
        src/3thparts/libcrc/crckrmit.c
        src/3thparts/libcrc/crcsick.c
        src/3thparts/libcrc/nmea-chk.c
        src/utilities/stringutils.cpp
        src/packages/aggregation.cpp
        src/head.cpp
        src/protocol.cpp)

target_include_directories (hgardenpi_protocol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

add_executable(hgardenpi_protocol_test
        test/protocoltest.cpp)

target_link_libraries(hgardenpi_protocol_test
        hgardenpi_protocol
        gtest
        gtest_main
        )