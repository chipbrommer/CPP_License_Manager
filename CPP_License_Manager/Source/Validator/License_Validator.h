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

			/// <summary>Gets the information of the lasts error in string format.</summary>
			/// <returns>String containing information about the last error.</returns>
			std::string GetLastError();
		protected:
		private:

			int8_t EditLicense(std::string license);

			LM_ERROR lastError = LM_ERROR::NO_LM_ERROR;			// Holds the last error
			License license = {};
		};
	}
}