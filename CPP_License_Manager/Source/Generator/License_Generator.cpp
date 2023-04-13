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

		int8_t Generator::SetLicenseStartDate(uint8_t month, uint8_t day, uint8_t year)
		{
			license.startDate.month = month;
			license.startDate.day = day;
			license.startDate.year = year;
			return 0;
		}

		int8_t Generator::SetLicenseEndDate(uint8_t month, uint8_t day, uint8_t year)
		{
			license.endDate.month = month;
			license.endDate.day = day;
			license.endDate.year = year;
			return 0;
		}

		int8_t Generator::SetLicenseIssuer()
		{
			return 0;
		}

		int8_t Generator::LoadLicenseInformationFromFile()
		{
			return 0;
		}

		void Generator::DisplayVersionInfo()
		{
			std::cout << std::format("License Manager v{}.{}.{}.{} \n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
		}

		std::string Generator::GetManagerVersionInfo()
		{
			return std::format("License Manager v{}.{}.{}.{} \n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
		}

	}
}
