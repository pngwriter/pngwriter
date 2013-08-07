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
SET(EXAMPLES_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples")
INCLUDE_DIRECTORIES(LIBRARY_SOURCES)


# build shared library
ADD_LIBRARY(pngwriter SHARED ${LIBRARY_SOURCES})
TARGET_LINK_LIBRARIES(pngwriter z png ${FREETYPE_LIBRARIES})

# build static library
ADD_LIBRARY(pngwriter_static STATIC ${LIBRARY_SOURCES})
SET_TARGET_PROPERTIES(pngwriter_static PROPERTIES OUTPUT_NAME pngwriter)
TARGET_LINK_LIBRARIES(pngwriter_static z png ${FREETYPE_LIBRARIES})

# build examples
SET(EXAMPLES_LIBS pngwriter_static ${FREETYPE_LIBRARIES})
#ADD_EXECUTABLE(pngtest ${EXAMPLES_SOURCES})
#TARGET_LINK_LIBRARIES(pngtest ${EXAMPLES_LIBS})

file(GLOB EXAMPLES_SOURCES ${EXAMPLES_SOURCES}/*.cc)

foreach(EXAMPLEFILE ${EXAMPLES_SOURCES})
    GET_FILENAME_COMPONENT(examplename ${EXAMPLEFILE} NAME)
    string(REPLACE ".cc" "" examplename ${examplename})
    SET(EXAMPLES_NAMES ${EXAMPLES_NAMES} ${examplename})
    MESSAGE("Found example: " ${examplename} " (" ${EXAMPLEFILE} ")")

#    ADD_EXECUTABLE(${examplename} ${EXAMPLEFILE})
#    TARGET_LINK_LIBRARIES(${examplename} ${EXAMPLES_LIBS})
endforeach( EXAMPLEFILE ${EXAMPLES_SOURCES} )


# Dependencies ################################################################
#
# external library: libPNG (mandatory)
FIND_PACKAGE(PNG REQUIRED)
INCLUDE_DIRECTORIES(${PNG_INCLUDE_PATH})

# external library: FreeType (optional)
INCLUDE(FindFreetype)
IF(FREETYPE_FOUND)
    INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})
ELSE(FREETYPE_FOUND)
    set_target_properties(pngwriter PROPERTIES COMPILE_FLAGS "-DNO_FREETYPE")
    set_target_properties(pngwriter_static PROPERTIES COMPILE_FLAGS
                          "-DNO_FREETYPE")
#    set_target_properties(pngtest PROPERTIES COMPILE_FLAGS "-DNO_FREETYPE")
ENDIF(FREETYPE_FOUND)


# Installation ################################################################
#
INSTALL(TARGETS pngwriter LIBRARY DESTINATION lib)
INSTALL(TARGETS pngwriter_static ARCHIVE DESTINATION lib)
#INSTALL(TARGETS pngtest RUNTIME DESTINATION bin)
