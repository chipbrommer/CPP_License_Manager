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

			// Catch if not open
			if (!licenseFile.is_open())
			{
				lastError = LM_ERROR::FILE_OPEN_ERROR;
				return false;
			}
			// Perform Validation
			else
			{
				// Get the current date;
				Date currentDate = {};
				GetDate(currentDate);

				// TODO decode.

				// Attempt to parse file into a license struct
				if (ParseLicenseTextFileToStruct(licenseFile, license) < 0)
				{
					lastError = LM_ERROR::LICENSE_PARSE_FAIL;
					return false;
				}

				// Check if dates are valid
				if (currentDate < license.startDate)
				{
					lastError = LM_ERROR::LICENSE_PREDATED;
				}
				else if (currentDate > license.endDate)
				{
					lastError = LM_ERROR::LICENSE_EXPIRED;
				}

				// If this is the first run, set the hardware information. 
				if (!license.hardware.isSet())
				{
					SetHardware();
				}
				else // Else, verify the hardware is the same. 
				{
					if (PerformHardwareTest() < 0)
					{
						lastError = LM_ERROR::HW_VALID_FAIL;
						return -1;
					}
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
	
		int8_t Validator::GetHardware(Hardware& hw)
		{
			std::string mac = {};
			std::string ip = {};
			std::string serial = {};

			Essentials::CPP_License_Manager::GetEthernetAdapterInformation(mac, ip);
			std::cout << std::format("Address: {}, Mac: {}\n", ip, mac);

			Essentials::CPP_License_Manager::DisplayVolumeInformations(serial);
			std::cout << std::format("C: Serial Num {}\n", serial);
			
			return 0;
		}
	
		int8_t Validator::PerformHardwareTest()
		{
			return -1;
		}
	}
}