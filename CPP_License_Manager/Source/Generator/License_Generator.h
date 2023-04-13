#pragma once

#ifdef _WIN32
#include <stdint.h>		// standard integers
#endif

#include <iostream>		// console out
#include <format>		// C++ string formats for C++20 and up

namespace Essentials
{
	namespace CPP_License_Manager
	{
		class Generator
		{
		public:
			Generator();
			~Generator();
			int8_t GenerateNewLicense();
			int8_t SetLicenseKey();
			int8_t SetLicenseStartDate();
			int8_t SetLicenseEndDate();
			int8_t SetLicenseIssuer();
			int8_t GenerateLicenseFromFile();
			void DisplayVersionInfo();

		protected:
		private:
		};
	}
}