#pragma once

#ifdef _WIN32
#include <stdint.h>		// standard integers
#endif

#include <iostream>		// console out
#include <fstream>		// File input
#include <format>		// C++ string formats for C++20 and up
#include "../License_Manager_Info.h"

namespace Essentials
{
	namespace CPP_License_Manager
	{
		class Generator
		{
		public:
			/// <summary>General Constructor.</summary>
			Generator();

			/// <summary>General Deconstructor.</summary>
			~Generator();

			/// <summary>Generates a new license.</summary>
			/// <returns>-1 on fail. 0 on success.</returns>
			int8_t GenerateNewLicense();

			/// <summary>Sets the license key to be used.</summary>
			/// <returns>-1 on fail. 0 on success.</returns>
			int8_t SetLicenseKey();

			/// <summary>Set the start date for a new license.</summary>
			/// <param name="month"> -[in]- Month to start on.</param>
			/// <param name="day"> -[in]- Day to start on.</param>
			/// <param name="year"> -[in]- Year to start on.</param>
			/// <returns>-1 on fail. 0 on success.</returns>
			int8_t SetLicenseStartDate(uint8_t month, uint8_t day, uint8_t year);

			/// <summary> Set the end date for a new license.</summary>
			/// <param name="month"> -[in]- Month to end on.</param>
			/// <param name="day"> -[in]- Day to end on.</param>
			/// <param name="year"> -[in]- Year to end on.</param>
			/// <returns>-1 on fail. 0 on success.</returns>
			int8_t SetLicenseEndDate(uint8_t month, uint8_t day, uint8_t year);

			/// <summary>Set the information for who issued the license.</summary>
			/// <param name="id"> -[in]- User ID</param>
			/// <param name="name"> -[in]- User Name</param>
			/// <param name="email"> -[in]- User Email</param>
			/// <returns>-1 on fail. 0 on success.</returns>
			int8_t SetLicenseIssuer(uint8_t id, char* name, char* email);

			/// <summary>Read in license information from a text file.</summary>
			/// <param name="filePath"> -[in]- Full file path to the file.</param>
			/// <returns>-1 on fail. 0 on success.</returns>
			int8_t LoadLicenseInformationFromFile(std::string& filePath);

			/// <summary>Displays the current tool version to console.</summary>
			void DisplayVersionInfo();

			/// <summary>Returns the current tool version in string format</summary>
			/// <returns> -[out]- A string containing the version information</returns>
			std::string GetManagerVersionInfo();

		protected:
		private:
			uint8_t	key;				// Holds the key used to encrypt the data. 
			Date	startDate;			// Holds the start date parsed from file or set by user. 
			Date	endDate;			// Holds the end date parsed from file or set by user.
			Issuer	issuer;				// Holds the issuer info parsed from file or set by user.
			License license;			// Holds the license to be created.
			char	activationKey[24];	// Holds the generated activation license
		};
	}
}