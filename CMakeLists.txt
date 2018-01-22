# Copyright 2013-2018 Axel Huebl
#
# This file is part of PNGwriter.
#
# PNGwriter is free software: you can edistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# PNGwriter is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with PNGwriter.
# If not, see <http://www.gnu.org/licenses/>.

# Preamble ####################################################################
#
cmake_minimum_required(VERSION 3.0.1)

project(PNGwriter VERSION 0.7.0 LANGUAGES CXX)


# Options and Variants ########################################################
#
function(pngwriter_option name description default)
    set(PNGwriter_USE_${name} ${default} CACHE STRING "${description}")
    set_property(CACHE PNGwriter_USE_${name} PROPERTY
        STRINGS "ON;TRUE;AUTO;OFF;FALSE"
    )
    if(PNGwriter_HAVE_${name})
        set(PNGwriter_HAVE_${name} TRUE)
    else()
        set(PNGwriter_HAVE_${name})
    endif()
    set(PNGwriter_CONFIG_OPTIONS ${PNGwriter_CONFIG_OPTIONS} ${name} PARENT_SCOPE)
endfunction()

pngwriter_option(FREETYPE "Enable support for text via Freetype" AUTO)

set(BUILD_PERFORMANCE OFF CACHE STRING "Build Performance test (requires C++11)")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the build type, e.g. Debug." FORCE)
endif()


# Dependencies ################################################################
#
# external library: libPNG (mandatory)
find_package(PNG 1.2.9 REQUIRED)

# external library: zlib (mandatory)
find_package(ZLIB REQUIRED)

# external library: FreeType (optional)
if(PNGwriter_USE_FREETYPE STREQUAL AUTO)
    find_package(Freetype)
elseif(PNGwriter_USE_FREETYPE)
    find_package(Freetype REQUIRED)
endif()

if(FREETYPE_FOUND)
    set(PNGwriter_HAVE_FREETYPE TRUE)
endif()


# Targets #####################################################################
#
add_library(PNGwriter
    src/pngwriter.cc
    src/pngwriter.h
)

target_link_libraries(PNGwriter PUBLIC PNG::PNG)
target_link_libraries(PNGwriter PUBLIC ZLIB::ZLIB)
if(NOT WIN32)
    # automatically added on windows
    target_link_libraries(PNGwriter PRIVATE m)
endif()

if(PNGwriter_HAVE_FREETYPE)
    target_include_directories(PNGwriter SYSTEM PUBLIC ${FREETYPE_INCLUDE_DIRS})
    target_link_libraries(PNGwriter PUBLIC ${FREETYPE_LIBRARIES})
    target_compile_definitions(PNGwriter PUBLIC "-DUSE_FREETYPE")
    target_compile_definitions(PNGwriter PUBLIC ${FREETYPE_FLAGS})
else()
    target_compile_definitions(PNGwriter PUBLIC "-DNO_FREETYPE")
endif()

set_target_properties(PNGwriter PROPERTIES PUBLIC_HEADER "src/pngwriter.h")
target_include_directories(PNGwriter PUBLIC
    $<BUILD_INTERFACE:${PNGwriter_BINARY_DIR}/src>
    $<BUILD_INTERFACE:${PNGwriter_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# examples & tests
set(PNGwriter_examples lyapunov pngtest)
set(PNGwriter_tests blackwhite diamond readwrite)
if(BUILD_PERFORMANCE)
    list(APPEND PNGwriter_tests performance)
endif()

foreach(examplename IN LISTS PNGwriter_examples)
    add_executable(${examplename} examples/${examplename}.cc)
    target_link_libraries(${examplename} PRIVATE PNGwriter)
endforeach()
foreach(testname IN LISTS PNGwriter_tests)
    add_executable(${testname} tests/${testname}.cc)
    target_link_libraries(${testname} PRIVATE PNGwriter)
endforeach()

if(BUILD_PERFORMANCE)
    set_target_properties(performance PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON
    )
endif()


# Generate Files with Configuration Options ###################################
#
configure_file(
    ${PNGwriter_SOURCE_DIR}/PNGwriterConfig.cmake.in
    ${PNGwriter_BINARY_DIR}/PNGwriterConfig.cmake
    @ONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("PNGwriterConfigVersion.cmake"
    VERSION ${PNGwriter_VERSION}
    COMPATIBILITY SameMajorVersion # actually: SameMinorVersion
)


# Installs ####################################################################
#
# headers, libraries and exectuables
install(TARGETS PNGwriter EXPORT PNGwriterTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
    INCLUDES DESTINATION include
)

# CMake package file for find_package(PNGwriter::PNGwriter) in depending projects
install(EXPORT PNGwriterTargets
    FILE PNGwriterTargets.cmake
    NAMESPACE PNGwriter::
    DESTINATION lib/cmake/PNGwriter
)
install(
    FILES
        ${PNGwriter_BINARY_DIR}/PNGwriterConfig.cmake
        ${PNGwriter_BINARY_DIR}/PNGwriterConfigVersion.cmake
    DESTINATION lib/cmake/PNGwriter
)


# Tests #######################################################################
#
enable_testing()

set(REFERENCE_PNGS
    pngs/burro.png
    pngs/bw_16bit_rgba_20x20.png
    pngs/bw_8bit_rgba_20x20.png
    pngs/bw_16bit_rgb_20x20.png
    pngs/bw_8bit_rgb_20x20.png
)
file(COPY ${REFERENCE_PNGS} DESTINATION ${PNGwriter_BINARY_DIR})

foreach(examplename IN LISTS PNGwriter_examples)
    add_test(NAME example.${examplename}
        COMMAND ${examplename}
    )
endforeach()
foreach(testname IN LISTS PNGwriter_tests)
    if(testname STREQUAL blackwhite)
        add_test(NAME test.${testname}.16bit.rgb
            COMMAND ${testname} bw_16bit_rgb_20x20.png
        )
        add_test(NAME test.${testname}.16bit.rgba
            COMMAND ${testname} bw_16bit_rgba_20x20.png
        )
        add_test(NAME test.${testname}.8bit.rgba
            COMMAND ${testname} bw_8bit_rgba_20x20.png
        )
        add_test(NAME test.${testname}.8bit.rgb
            COMMAND ${testname} bw_8bit_rgb_20x20.png
        )
    else()
        add_test(NAME test.${testname}
            COMMAND ${testname}
        )
    endif()
endforeach()


# Status Message for Build Options ############################################
#
message("")
message("PNGwriter build configuration:")
message("  PNGwriter Version: ${PNGwriter_VERSION}")
message("  C++ Compiler : ${CMAKE_CXX_COMPILER_ID} "
                         "${CMAKE_CXX_COMPILER_VERSION} "
                         "${CMAKE_CXX_COMPILER_WRAPPER}")
message("    ${CMAKE_CXX_COMPILER}")
message("")
message("  Installation prefix: ${CMAKE_INSTALL_PREFIX}")
message("")
message("  Build Type: ${CMAKE_BUILD_TYPE}")
message("  Build Options:")

foreach(opt IN LISTS PNGwriter_CONFIG_OPTIONS)
  if(${PNGwriter_HAVE_${opt}})
    message("    ${opt}: ON")
  else()
    message("    ${opt}: OFF")
  endif()
endforeach()
message("")
