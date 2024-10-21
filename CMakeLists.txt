#
#  Copyright 2011-16 ARM Limited and Contributors.
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#    * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#    * Neither the name of ARM Limited nor the
#      names of its contributors may be used to endorse or promote products
#      derived from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY ARM LIMITED AND CONTRIBUTORS "AS IS" AND
#  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED. IN NO EVENT SHALL ARM LIMITED AND CONTRIBUTORS BE LIABLE FOR ANY
#  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
cmake_minimum_required(VERSION 3.26)

project(NE10
    VERSION 1.3.0
    LANGUAGES C CXX ASM)

option(NE10_BUILD_EXAMPLES "Build NE10 examples" OFF)

# hard float abi
option(NE10_ARM_HARD_FLOAT "Build NE10 for hard float abi" ON)

#unit test options
option(NE10_BUILD_UNIT_TEST "Build NE10 unit test" OFF)
if (NE10_BUILD_UNIT_TEST)
    #decide the test is smoke, regression or performance test, only one of
    #three options can be ON! And if you want to run performance test, you
    #should build the releave version, see the BUILD_DEBUG below.
    option(NE10_SMOKE_TEST "Run smoke test" OFF)
    option(NE10_REGRESSION_TEST "Run regression test" OFF)
    option(NE10_PERFORMANCE_TEST "Run performance test" OFF)

    option(NE10_DEBUG_TRACE "Print debug trace" OFF)
endif()

message("-- Ne10 target architecture: ${NE10_TARGET_ARCH}")

#select functionalities to be compiled
if("${NE10_TARGET_ARCH}" STREQUAL "armv7")
    # Math module has not been optimized for aarch64.
    option(NE10_ENABLE_MATH "Build math functionalities to NE10" OFF)
    # Physics module has not been optimized for aarch64.
    option(NE10_ENABLE_PHYSICS "Build physics functionalities to NE10" OFF)
endif()
option(NE10_ENABLE_DSP "Build dsp functionalities to NE10" ON)
option(NE10_ENABLE_IMGPROC "Build image processing functionalities to NE10" OFF)

set(NE10_VERSION 10)

add_compile_options(
    -fno-strict-aliasing
    $<$<CONFIG:DEBUG>:-Wall>
    $<$<CONFIG:DEBUG>:-Wno-unused-but-set-variable>
)

# By default, we compile c intrinsic.
option(NE10_ASM_OPTIMIZATION OFF)
message("-- Ne10 assembly optimization: ${NE10_ASM_OPTIMIZATION}")

set(CMAKE_C_STANDARD 99)

# Add NE10 library sub-directory.
add_subdirectory(modules)

if(NE10_BUILD_EXAMPLES AND NE10_ENABLE_MATH)
    add_subdirectory(samples)
endif()

if(NE10_BUILD_UNIT_TEST)
    add_subdirectory(test)
endif()

# Make sure we are compiling for an ARM system.
# This is a verbose fail-fast in case we are trying to compile for non-ARM;
# otherwise it would fail at `make` with obscure errors.
if(GNULINUX_PLATFORM AND (NOT CMAKE_SYSTEM_PROCESSOR MATCHES "^arm"))
    message(FATAL_ERROR "You are trying to compile for non-ARM (CMAKE_SYSTEM_PROCESSOR='${CMAKE_SYSTEM_PROCESSOR}')! see doc/building.md for cross compilation instructions.")
endif()
