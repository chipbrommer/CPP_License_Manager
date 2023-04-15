#pragma once

#ifdef _WIN32
#include <stdint.h>		// standard integers
#endif

#include <iostream>		// console out
#include <fstream>		// File input
#include <format>		// C++ string formats for C++20 and up
#include <vector>
#include "../License_Manager_Utilities.h"

namespace Essentials
{
	namespace CPP_License_Manager
	{
		class Validator
		{
		public:
			/// <summary>General Constructor.</summary>
			Validator();

			/// <summary>General Deconstructor.</summary>
			~Validator();

			/// <summary>Validates a license file</summary>
			/// <param name="licensePath"> -[in]- File path to the license.</param>
			/// <returns>True = good license, False = bad license. 
			/// Call GetLastError to know more.</returns>
			bool Validate(std::string licensePath);

			/// <summary>Displays the current tool version to console.</summary>
			void DisplayVersionInfo();

			/// <summary>Displays the current license data</summary>
			void DisplayLicenseData();

			/// <summary>Returns the current tool version in string format</summary>
			/// <returns> -[out]- A string containing the version information</returns>
			std::string GetManagerVersionInfo();

			/// <summary>Gets the information of the lasts error in string format.</summary>
			/// <returns>String containing information about the last error.</returns>
			std::string GetLastError();
		protected:
		private:

			/// <summary>Updates a license hardware section for the current running platform.</summary>
			/// <returns>True = success, False = fail.</returns>
			bool UpdateLicenseHardware();

			int8_t EditLicense(std::string licensePath);

			LM_ERROR lastError = LM_ERROR::NO_LM_ERROR;			// Holds the last error
			License license = {};
		};
	}
}