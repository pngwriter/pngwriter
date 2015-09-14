CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Projekt name ################################################################
#
PROJECT(pngwriter)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH
        "install prefix" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# set helper pathes to find libraries and packages on some 64bit machines
set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/")

# Warnings ####################################################################
#
# GNU
IF(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
# Clang
ELSEIF(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
# ICC
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
# PGI
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "PGI")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Minform=inform")
ENDIF()

# Dependencies ################################################################
#
# external library: libPNG (mandatory)
FIND_PACKAGE(PNG 1.2.9 REQUIRED)
INCLUDE_DIRECTORIES(${PNG_INCLUDE_DIRS})

# external library: zlib (mandatory)
FIND_PACKAGE(ZLIB REQUIRED)
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIRS})

# external library: FreeType (optional)
INCLUDE(FindFreetype)
IF(FREETYPE_FOUND)
    INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
    SET(FREETYPE_FLAGS "-DUSE_FREETYPE")
ELSE(FREETYPE_FOUND)
    SET(FREETYPE_FLAGS "-DNO_FREETYPE")
    SET(FREETYPE_LIBRARIES "")
ENDIF(FREETYPE_FOUND)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FREETYPE_FLAGS}")

# Sources and targets #########################################################
#
# add includes and sources
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/src" LIBRARY_SOURCES)
GET_FILENAME_COMPONENT(LIBRARY_INCLUDES ${LIBRARY_SOURCES} PATH)
SET(EXAMPLES_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples")
SET(TESTS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests")
INCLUDE_DIRECTORIES(${LIBRARY_INCLUDES})

# build shared library
ADD_LIBRARY(pngwriter SHARED ${LIBRARY_SOURCES})
TARGET_LINK_LIBRARIES(pngwriter m ${ZLIB_LIBRARIES} ${PNG_LIBRARIES} ${FREETYPE_LIBRARIES})

# build static library
ADD_LIBRARY(pngwriter_static STATIC ${LIBRARY_SOURCES})
SET_TARGET_PROPERTIES(pngwriter_static PROPERTIES OUTPUT_NAME pngwriter)
TARGET_LINK_LIBRARIES(pngwriter_static m ${ZLIB_LIBRARIES} ${PNG_LIBRARIES} ${FREETYPE_LIBRARIES})

# build examples and tests
SET(EXAMPLES_LIBS pngwriter_static ${FREETYPE_LIBRARIES})
FILE(GLOB EXAMPLES_SOURCES ${EXAMPLES_SOURCES}/*.cc ${TESTS_SOURCES}/*.cc)
# needs CXXFLAGS="-std=c++11"
LIST(REMOVE_ITEM EXAMPLES_SOURCES "${TESTS_SOURCES}/performance.cc")

FOREACH(EXAMPLEFILE ${EXAMPLES_SOURCES})
    GET_FILENAME_COMPONENT(examplename ${EXAMPLEFILE} NAME)
    STRING(REPLACE ".cc" "" examplename ${examplename})
    SET(EXAMPLES_NAMES ${EXAMPLES_NAMES} ${examplename})
    #MESSAGE("Found example: " ${examplename} " (" ${EXAMPLEFILE} ")")

    ADD_EXECUTABLE(${examplename} ${EXAMPLEFILE})
    TARGET_LINK_LIBRARIES(${examplename} ${EXAMPLES_LIBS})
ENDFOREACH(EXAMPLEFILE ${EXAMPLES_SOURCES})

# Installation ################################################################
#
INSTALL(TARGETS pngwriter LIBRARY DESTINATION lib)
INSTALL(TARGETS pngwriter_static ARCHIVE DESTINATION lib)

# they are test binaries and should not be installed, but tested
#foreach(EXAMPLENAME ${EXAMPLES_NAMES})
#    INSTALL(TARGETS ${EXAMPLENAME} RUNTIME DESTINATION bin)
#endforeach(EXAMPLENAME ${EXAMPLES_NAMES})

# add pngwriter.h in include/
#
INSTALL(FILES ${LIBRARY_INCLUDES}/pngwriter.h DESTINATION include)

# to do: install fonts, to shared/... too?
#
