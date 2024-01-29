
cmake_minimum_required(VERSION 3.10)
project(unitTest)

set(CMAKE_C_STANDARD 23)
set(CMAKE_OSX_SYSROOT /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk)

add_compile_options(
    -ggdb
    -Wall
    -Wextra
    -Wreturn-type
    -Wunused
    -Weverything

    -Wno-declaration-after-statement
    -Wno-missing-prototypes
    -Wno-vla
    -Wno-format-nonliteral
    -Wno-multichar
    -Wno-gnu-pointer-arith

    -pedantic
    -fblocks
    -O0
)

add_link_options(
    -ggdb
    -fblocks

    # -fsanitize=address
)

add_library(unitTest unitTest.h unitTest.c)

add_executable(test_UnitTests test_unitTest.c)
target_link_libraries(test_UnitTests PUBLIC unitTest)