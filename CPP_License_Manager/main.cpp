// CPP_License_Manager.cpp : Defines the entry point for the application.
//

#include "Source/License_Manager.h"

int main()
{
	std::cout << "Hello CMake.\n\n";

	Essentials::CPP_License_Manager::Generator generator;
	generator.GenerateNewLicense();

	return 0;
}
