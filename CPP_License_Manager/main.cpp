// CPP_License_Manager.cpp : Defines the entry point for the application.
//

#include "Source/License_Manager.h"

int main()
{
	std::cout << "Hello CMake.\n\n";

	Essentials::CPP_License_Manager::Generator generator;
	if (generator.GenerateNewLicense() < 0)
	{
		std::cout << generator.GetLastError();
	}


	if (generator.SetLicenseIssuer(13, (char*)"Chip Brommer", (char*)"chipbrommer@gmail.com") < 0)
	{
		std::cout << generator.GetLastError();
	}
	else
	{
		generator.DisplayLicenseData();
	}

	return 0;
}
