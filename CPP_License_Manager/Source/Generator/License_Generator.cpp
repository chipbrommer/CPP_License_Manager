#include "License_Generator.h"

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
			// Set the License Manager info
			license.managerInfo.versionMajor = VERSION_MAJOR;
			license.managerInfo.versionMinor = VERSION_MINOR;

			// Verify data is set, no return on error because its not imperative YET. 
			if (!license.managerInfo.isSet())
			{
				lastError = LM_ERROR::MANAGER_INFO_NOT_SET;
			}

			// Check if we have all the basic necessary data
			if (!license.isReady())
			{
				// TODO - figure out what part is missing and display appropriate error
				return -1;
			}

			std::cout << "New License!\n";
			// Return success
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

			// If set, return success
			if (license.startDate.isSet())
			{
				return 0;
			}

			// Return failure.
			lastError = LM_ERROR::START_DATE_NOT_SET;
			return -1;
		}

		int8_t Generator::SetLicenseEndDate(uint8_t month, uint8_t day, uint8_t year)
		{
			license.endDate.month = month;
			license.endDate.day = day;
			license.endDate.year = year;

			// If set, return success
			if (license.endDate.isSet())
			{
				return 0;
			}

			// Return failure.
			lastError = LM_ERROR::END_DATE_NOT_SET;
			return -1;
		}

		int8_t Generator::SetLicenseIssuer(uint8_t id, char* name, char* email)
		{
			license.issuer.id = id;
			memcpy(license.issuer.name, name, sizeof(license.issuer.name - 1));
			memcpy(license.issuer.email, email, sizeof(license.issuer.email - 1));

			// TODO - set the current dat and time of this function call. 
			

			// If set, return success
			if (license.issuer.isSet())
			{
				return 0;
			}

			// Find the reason for error
			if(!license.issuer.issueDate.isSet()) { lastError = LM_ERROR::ISSUE_DATE_NOT_SET; }
			else if (!license.issuer.issueTime.isSet()) { lastError = LM_ERROR::ISSUE_TIME_NOT_SET; }
			else{ lastError = LM_ERROR::ISSUER_INFO_NOT_SET; }

			// Return failure.
			return -1;
		}

		int8_t Generator::LoadLicenseInformationFromFile(std::string& filePath)
		{
			std::ofstream licenseFile;
			licenseFile.open(filePath);

			if (!licenseFile.is_open())
			{
				std::cerr << "Error opening file [%s].\n", filePath.c_str();
				return -1;
			}
			else
			{
				// Find the data points that are set and map them to the license. 
			}

			// Close file
			licenseFile.close();

			return 0;
		}

		void Generator::DisplayVersionInfo()
		{
			std::cout << std::format("License Manager v{}.{}.{}.{} \n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
		}

		std::string Generator::GetManagerVersionInfo()
		{
			return std::format("v{}.{}.{}.{} \n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
		}
	}
}
