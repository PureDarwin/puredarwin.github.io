cmake_minimum_required(VERSION 3.16)
project(pdnews VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(pdnews src/pdnews.c)
target_compile_definitions(pdnews PRIVATE _POSIX_C_SOURCE=200809L)
target_compile_options(pdnews PRIVATE -Wall -Wextra)

include(GNUInstallDirs)
install(TARGETS pdnews RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
