# CMakeList.txt : CMake project for CPP_License_Manager, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CPP_License_Manager   
"main.cpp" 
"Source/Generator/License_Generator.cpp" 
"Source/Generator/License_Generator.h" 
"Source/Inspector/License_Inspector.cpp" 
"Source/Inspector/License_Inspector.h" 
"Source/Validator/License_Validator.cpp" 
"Source/Validator/License_Validator.h" 
"Source/License_Manager.h" 
"Source/License_Manager_Info.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CPP_License_Manager PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
