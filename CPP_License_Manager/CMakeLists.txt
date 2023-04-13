# CMakeList.txt : CMake project for CPP_License_Manager, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (CPP_License_Manager   "main.cpp" "License_Generator.cpp" "License_Generator.h" "License_Inspector.cpp" "License_Inspector.h" "License_Validator.cpp" "License_Validator.h" "License_Manager.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CPP_License_Manager PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
