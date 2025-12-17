cmake_minimum_required(VERSION 3.11)

project(Lumina CXX)


if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()

# ---------------------------------------------------------------------------------------
# Example of using pre-compiled library
# ---------------------------------------------------------------------------------------
add_executable(Lumina main.cpp)
target_link_libraries(Lumina PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)