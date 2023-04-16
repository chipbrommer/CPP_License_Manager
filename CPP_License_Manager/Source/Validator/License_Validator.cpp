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
			std::fstream licenseFile;
			licenseFile.open(licensePath, std::ios::in);

			// Flag for if need to rewrite data to file. 
			bool rewrite = false;

			// Catch if not open
			if (!licenseFile.is_open())
			{
				lastError = LM_ERROR::FILE_OPEN_ERROR;
				return false;
			}

			// Perform Validation
			if (licenseFile.good())
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
					return false;
				}
				else if (currentDate > license.endDate)
				{
					lastError = LM_ERROR::LICENSE_EXPIRED;
					return false;
				}

				// If this is the first run, set the hardware information. 
				if (!license.hardware.isSet())
				{
					if (GetHardware(license.hardware) < 0)
					{
						lastError = LM_ERROR::GET_HW_FAIL;
					}

					rewrite = true;

				}
				// Else, verify the hardware is the same.
				else 
				{
					if (PerformHardwareTest() < 0)
					{
						lastError = LM_ERROR::HW_VALID_FAIL;
						return false;
					}
				}
			
				// If we need to rewrite data, do it here. 
				if (rewrite)
				{
					// close it from read only and open as output. 
					licenseFile.close();

					std::fstream nl;

					nl.open(licensePath, std::ios::out | std::ios::trunc);
					nl.seekg(0, std::ios::beg);

					WriteLicense(nl,license);

					nl.close();

					return true;
				}
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

			GetEthernetAdapterInformation(mac, ip);

			// Attempt to parse the MAC with a delimiter. 
			for (uint8_t i = 0; i < sizeof(LM_Delimiters); i++)
			{
				// Parse the mac address string into individual string for each hex 
				std::vector<std::string> fullMac = SplitString(mac, LM_Delimiters[i]);

				if (fullMac.size() == 6)
				{
					// iterate the vector and store.

					// Break out of fop loop once delimiter is found and data parsed
					break;
				}
			}

			// Attempt to parse the IP with a delimiter. 
			for (uint8_t i = 0; i < sizeof(LM_Delimiters); i++)
			{
				// Parse the mac address string into individual string for each hex 
				std::vector<std::string> fullIP = SplitString(ip, LM_Delimiters[i]);

				if (fullIP.size() == 4)
				{
					// store the IP
					hw.ipAddress[0] = std::stoi(fullIP[0]);
					hw.ipAddress[1] = std::stoi(fullIP[1]);
					hw.ipAddress[2] = std::stoi(fullIP[2]);
					hw.ipAddress[3] = std::stoi(fullIP[3]);

					// Break out of fop loop once delimiter is found and data parsed
					break;
				}
			}

			// Attempt to get the system volume information.
			DisplayVolumeInformations(serial);

			// copy into struct
			memcpy(hw.volumeSerialNumber, serial.c_str(), sizeof(hw.volumeSerialNumber));

			// Return success
			return 0;
		}
	
		int8_t Validator::PerformHardwareTest()
		{
			return -1;
		}
	}
}