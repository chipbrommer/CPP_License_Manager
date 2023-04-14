// CPP_License_Manager.cpp : Defines the entry point for the application.
//

#include "Source/License_Manager.h"

int main()
{
	std::cout << "Hello CMake.\n\n";

	Essentials::CPP_License_Manager::Generator generator;
	generator.SetLicenseStartDate(4, 15, 2023);
	generator.SetLicenseEndDate(4, 16, 2024);
	generator.SetLicenseKey();


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
