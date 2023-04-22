# CMakeList.txt : CMake project for CPP_License_Manager, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CPP_License_Manager   
"main.cpp" 
"Source/Generator/License_Generator.cpp" 
"Source/Generator/License_Generator.h" 
"Source/Validator/License_Validator.cpp" 
"Source/Validator/License_Validator.h" 
"Source/License_Manager.h" 
"Source/License_Manager_Info.h"
"Source/License_Manager_Utilities.h"
 "Source/License_Manager_Keys.h")

# CMake policy adds escape after defintions 
cmake_policy(SET CMP0005 NEW)

# Created definition and variables
set(LICENSE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/License/")

# Create a "LICENSE_PATH" definition to the current source directory. 
add_definitions(-DLICENSE_PATH="${LICENSE_DIR}")

# Create a license directory at install time. 
install(DIRECTORY DESTINATION ${LICENSE_DIR})

# Make sure directories exist at compile time
file(MAKE_DIRECTORY ${LICENSE_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${LICENSE_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CPP_License_Manager PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
