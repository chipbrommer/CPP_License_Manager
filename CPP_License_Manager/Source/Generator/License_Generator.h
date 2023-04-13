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
			int8_t SetLicenseStartDate(uint8_t month, uint8_t day, uint8_t year);
			int8_t SetLicenseEndDate(uint8_t month, uint8_t day, uint8_t year);
			int8_t SetLicenseIssuer();
			int8_t LoadLicenseInformationFromFile();
			void DisplayVersionInfo();
			std::string GetManagerVersionInfo();

		protected:
		private:
			uint8_t	key;				//! Holds the key used to encrypt the data. 
			Date	startDate;			//! Holds the start date parsed from file or set by user. 
			Date	endDate;			//! Holds the end date parsed from file or set by user.
			Issuer	issuer;				//! Holds the issuer info parsed from file or set by user.
			License license;			//! Holds the license to be created.
			char	activationKey[24];	//! Holds the generated activation license
		};
	}
}