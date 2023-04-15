#include "License_Validator.h"

namespace Essentials
{
	namespace CPP_License_Manager
	{
		Validator::Validator()
		{

		}

		Validator::~Validator()
		{

		}

		bool Validator::Validate(std::string licensePath)
		{
			// Create filestream and open filePath
			std::ifstream licenseFile;
			licenseFile.open(licensePath);

			// Verify open.
			if (!licenseFile.is_open())
			{
				lastError = LM_ERROR::FILE_OPEN_ERROR;
				return false;
			}

			else
			{
				// Get the current date;
				Date currentDate = {};
				GetDate(currentDate);

				// TODO decode.

				ParseLicenseTextFileToStruct(licenseFile, license);

				if (currentDate < license.startDate)
				{
					lastError = LM_ERROR::LICENSE_PREDATED;
				}
				else if (currentDate > license.endDate)
				{
					lastError = LM_ERROR::LICENSE_EXPIRED;
				}

				// return good
				return true;
			}

			// Default return
			return false;
		}
	
		void Validator::DisplayVersionInfo()
		{
			std::cout << std::format("License Manager v{}.{}.{}.{} \n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
		}

		void Validator::DisplayLicenseData()
		{
			license.display();
		}

		std::string Validator::GetManagerVersionInfo()
		{
			return std::format("v{}.{}.{}.{} \n\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD);
		}

		std::string Validator::GetLastError()
		{
			return ErrorMap[lastError];
		}
	
		int8_t Validator::EditLicense(std::string licensePath)
		{
			//char* macAddress = GetMacAddress();
			//
			//if (macAddress != NULL)
			//{
			//	memcpy(license.hardware.userMacAddress, macAddress, sizeof(license.hardware.userMacAddress));
			//}
			
			return 0;
		}
	}
}