cmake_minimum_required(VERSION 3.16)

project(hgardenpi_protocol  VERSION "0.10.0" LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

#test macro
set(TEST 1)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

configure_file(config.h.in ../src/config.h)
include_directories("include")
include_directories("/usr/include/machine/")

add_library(hgardenpi_protocol
        include/hgardenpi-protocol/3thparts/CRC.h
        include/hgardenpi-protocol/packages/aggregation.hpp
        include/hgardenpi-protocol/packages/station.hpp
        include/hgardenpi-protocol/packages/synchro.hpp
        include/hgardenpi-protocol/utils/shiftutils.hpp
        include/hgardenpi-protocol/utils/stringutils.hpp
        include/hgardenpi-protocol/constants.hpp
        include/hgardenpi-protocol/head.hpp
        include/hgardenpi-protocol/protocol.hpp
        src/utils/shiftutils.cpp
        src/utils/stringutils.cpp
        src/protocol.cpp
        )

add_executable(hgardenpi_protocol_test
        test/test.cpp
        test/sendtest.cpp
        )

target_link_libraries(hgardenpi_protocol_test
        hgardenpi_protocol
        gtest
        gtest_main
        )