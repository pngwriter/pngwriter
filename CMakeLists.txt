cmake_minimum_required(VERSION 2.6)

# Projekt name ################################################################
#
project (pngwriter)

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH
        "install prefix" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT) 


# Sources and targets #########################################################
#
# add includes and sources
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/src" LIBRARY_SOURCES)
INCLUDE_DIRECTORIES(${PNG_INCLUDE_PATH})

# build shared library
ADD_LIBRARY(pngwriter SHARED ${LIBRARY_SOURCES})
TARGET_LINK_LIBRARIES(pngwriter z png ${FREETYPE_LIBRARIES})

# build static library
ADD_LIBRARY(pngwriter_static STATIC ${LIBRARY_SOURCES})
SET_TARGET_PROPERTIES(pngwriter_static PROPERTIES OUTPUT_NAME pngwriter)
TARGET_LINK_LIBRARIES(pngwriter_static z png ${FREETYPE_LIBRARIES})


# Dependencies ################################################################
#
# external library: libPNG (mandatory)
FIND_PACKAGE(PNG REQUIRED)

# external library: FreeType (optional)
INCLUDE(FindFreetype)
IF(FREETYPE_FOUND)
    INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
ELSE(FREETYPE_FOUND)
    set_target_properties(pngwriter PROPERTIES COMPILE_FLAGS "-DNO_FREETYPE")
    set_target_properties(pngwriter_static PROPERTIES COMPILE_FLAGS
                          "-DNO_FREETYPE")
ENDIF(FREETYPE_FOUND)


# Installation ################################################################
#
INSTALL(TARGETS pngwriter LIBRARY DESTINATION lib)
INSTALL(TARGETS pngwriter_static ARCHIVE DESTINATION lib)
