// CPP_License_Manager.cpp : Defines the entry point for the application.
//

#include "Source/License_Manager.h"

int main()
{

	Essentials::CPP_License_Manager::Generator generator;
	
	std::string fp = std::string(LICENSE_PATH) + "textpathfile.txt";

	generator.SetLicenseStartDate(4, 15, 2023);

	generator.SetLicenseEndDate(4, 16, 2024);

	generator.LoadLicenseInformationFromFile(fp);

	if (generator.SetLicenseIssuer(13, (char*)"Chip Brommer", (char*)"chipbrommer@gmail.com") < 0)
	{
		std::cout << generator.GetLastError();
	}

	generator.GenerateNewLicense();

	generator.DisplayLicenseData();

	std::cout << "\n\n\n\n\n";

	Essentials::CPP_License_Manager::Validator validator;

	if (validator.Validate(fp))
	{
		std::cout << "\n\tLICENSE VALID!\n";
		validator.DisplayLicenseData();
	}
	else
	{
		std::cout << "Failed to parse license file!\n";
		std::cout << "Call for assistance!\n";
		std::cout << validator.GetLastError();
	}

	return 0;
}
