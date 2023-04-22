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
			license.managerInfo.setVersion(VERSION_MAJOR, VERSION_MINOR);

			// Verify data is set, no return on error because its not imperative YET. 
			if (!license.managerInfo.isSet())
			{
				lastError = LM_ERROR::MANAGER_INFO_NOT_SET;
			}

			// Check if we have all the basic necessary data
			if (!license.isReady())
			{
				if		(!license.managerInfo.isSet())	{ lastError = LM_ERROR::MANAGER_INFO_NOT_SET; }
				else if (!license.issuer.isReady())		{ lastError = LM_ERROR::ISSUE_DATE_NOT_SET; }
				else if (!license.startDate.isSet())	{ lastError = LM_ERROR::START_DATE_NOT_SET; }
				else if (!license.endDate.isSet())		{ lastError = LM_ERROR::END_DATE_NOT_SET; }
				return -1;
			}

			if (Encrypt(license) < 0)
			{
				return -1;
			};

			// Return success
			return 0;
		}

		int8_t Generator::SetLicenseKey()
		{
			return 0;
		}

		int8_t Generator::SetLicenseStartDate(uint8_t month, uint8_t day, uint16_t year)
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

		int8_t Generator::SetLicenseEndDate(uint8_t month, uint8_t day, uint16_t year)
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
			memcpy(license.issuer.name, name, sizeof(license.issuer.name));
			memcpy(license.issuer.email, email, sizeof(license.issuer.email));

			GetDateAndTime(license.issuer.issueDate, license.issuer.issueTime);

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

		int8_t Generator::LoadLicenseInformationFromFile(std::string filePath)
		{
			// Create file and open filePath
			std::fstream licenseFile;
			licenseFile.open(filePath, std::ios::in);

			// Verify open.
			if (!licenseFile.is_open())
			{
				lastError = LM_ERROR::FILE_OPEN_ERROR;
				return -1;
			}
			else
			{
				ParseLicenseTextFileToStruct(licenseFile, license);
			}

			// Close file
			licenseFile.close();

			// Verify file closed.
			if (licenseFile.is_open()) { lastError = LM_ERROR::FILE_CLOSE_ERROR; return -1; }

			// Verify start date and end date are set
			if (!license.startDate.isSet()) { lastError = LM_ERROR::START_DATE_NOT_SET; return -1; }
			if (!license.endDate.isSet()) { lastError = LM_ERROR::END_DATE_NOT_SET;	return -1; }

			// Return success.
			return 0;
		}

		void Generator::DisplayVersionInfo()
		{
			std::cout << std::format("License Manager v{}.{}.{}.{} \n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
		}

		void Generator::DisplayLicenseData()
		{
			license.display();
		}

		std::string Generator::GetManagerVersionInfo()
		{
			return std::format("v{}.{}.{}.{} \n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
		}

		std::string Generator::GetLastError()
		{
			return ErrorMap[lastError];
		}
	}
}
