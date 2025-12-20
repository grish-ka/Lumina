#
#    Copyright 2025 grish-ka
#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

cmake_minimum_required(VERSION 3.11)
project(Lumina CXX)

# --- Dependencies ---
if(NOT TARGET spdlog)
    find_package(spdlog REQUIRED)
endif()

# --- Executable Definition ---
add_executable(Lumina
        main.cpp
        lexer.cpp
        lexer.h
        Parser.cpp
        Parser.h
        ast.h
)

target_link_libraries(Lumina PRIVATE
        spdlog::spdlog
        $<$<BOOL:${MINGW}>:ws2_32>
)

# ---------------------------------------------------------------------------------------
# 📦 INSTALLATION RULES (Required for CPack)
# ---------------------------------------------------------------------------------------
include(GNUInstallDirs)

# Install the binary to /usr/local/bin (or equivalent)
install(TARGETS Lumina
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ---------------------------------------------------------------------------------------
# 🎁 CPACK CONFIGURATION
# ---------------------------------------------------------------------------------------
set(CPACK_PACKAGE_NAME "Lumina")
set(CPACK_PACKAGE_VENDOR "grish-ka")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Lumina AOT Compiler for aarch64")
set(CPACK_PACKAGE_VERSION "1.0.0")

# Package generators: .tar.gz for generic Linux, .deb for Ubuntu/Debian
set(CPACK_GENERATOR "TGZ;DEB")

# Debian specific settings
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "grish-ka")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

include(CPack)