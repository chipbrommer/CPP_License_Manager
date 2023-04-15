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

		bool Validator::Validate(std::string license)
		{
			// Create filestream and open filePath
			std::ifstream licenseFile;
			licenseFile.open(license);

			// Verify open.
			if (!licenseFile.is_open())
			{
				lastError = LM_ERROR::FILE_OPEN_ERROR;
				return false;
			}
			else
			{
				// Get the current date;
				Date t = {};
				GetDate(t);

				// TODO decode.


				return true;
			}

			// Default return
			return false;
		}
	
		std::string Validator::GetLastError()
		{
			return ErrorMap[lastError];
		}
	
		int8_t Validator::EditLicense(std::string license)
		{
			return -1;
		}
	}
}