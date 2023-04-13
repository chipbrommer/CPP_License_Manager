#include "License_Generator.h"
#include "../License_Manager_Info.h"

namespace Essentials
{
	namespace CPP_License_Manager
	{
		Generator::Generator()
		{

		}

		Generator::~Generator()
		{

		}

		int8_t Generator::GenerateNewLicense()
		{
			std::cout << "New License!\n";
			return 0;
		}

		int8_t Generator::SetLicenseKey()
		{
			return 0;
		}

		int8_t Generator::SetLicenseStartDate()
		{
			return 0;
		}

		int8_t Generator::SetLicenseEndDate()
		{
			return 0;
		}

		int8_t Generator::SetLicenseIssuer()
		{
			return 0;
		}

		int8_t Generator::GenerateLicenseFromFile()
		{
			return 0;
		}

		void Generator::DisplayVersionInfo()
		{
			std::cout << std::format("License Manager v{}.{}.{}.{} \n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
		}

	}
}
