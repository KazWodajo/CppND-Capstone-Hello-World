cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(ShoppingCart LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#------------------------INCLUSION OF Qt----------------------#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt5 REQUIRED
	COMPONENTS Core
				Widgets
)#------------------------INCLUSION OF PROJECT FILES----------------------#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

file(GLOB_RECURSE SOURCES
	"${FORMS_DIR}/*.ui"
	"${FORMS_DIR}/*.qrc"
	"${INCLUDE_DIR}/*.h"
	"${SOURCE_DIR}/*.cpp"
)

#=================== SETUP EXECTUABLE ====================#
# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Add the executable
add_executable(ShoppingCart WIN32 ${SOURCES})

# Add the target includes for ShoppingCart 
target_include_directories(ShoppingCart PRIVATE ${FORMS_DIR})
target_include_directories(ShoppingCart PRIVATE ${INCLUDE_DIR})
target_include_directories(ShoppingCart PRIVATE ${SOURCE_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(ShoppingCart Qt5::Widgets)



