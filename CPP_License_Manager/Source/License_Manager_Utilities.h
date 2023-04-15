#pragma once

#ifdef _WIN32
#include <stdint.h>		// standard integers
#endif

#include <iostream>		// console out
#include <fstream>		// File input
#include <format>		// C++ string formats for C++20 and up
#include <vector>
#include "License_Manager_Info.h"

namespace Essentials
{
	namespace CPP_License_Manager
	{

		/// <summary>Gets the current date</summary>
		/// <param name="date"> -[out]- Date structure to store date into.</param>
		/// <returns>-1 on fail. 0 on success.</returns>
		static int8_t GetDate(Date& date)
		{
			time_t now = time(0);
			tm local_tm = {};
			localtime_s(&local_tm, &now);

			date.month = local_tm.tm_mon + 1;
			date.day = local_tm.tm_mday;
			date.year = 1900 + local_tm.tm_year;

			if (!date.isSet())
			{
				return -1;
			}

			return 0;
		}

		/// <summary>Gets the current time</summary>
		/// <param name="t"> -[out]- Time structure to store time into.</param>
		/// <returns>-1 on fail. 0 on success.</returns>
		static int8_t GetTime(Time& t)
		{
			time_t now = time(0);
			tm local_tm = {};
			localtime_s(&local_tm, &now);

			t.hour = local_tm.tm_hour;
			t.minute = local_tm.tm_min;
			t.second = local_tm.tm_sec;

			if (!t.isSet())
			{
				return -1;
			}

			return 0;
		}

		/// <summary>Gets the current date and time</summary>
		/// <param name="date"> -[out]- Date structure to store date into.</param>
		/// <param name="t"> -[out]- Time structure to store time into.</param>
		/// <returns>-1 on fail. 0 on success.</returns>
		static int8_t GetDateAndTime(Date& date, Time& time)
		{
			if (GetDate(date) < 0) { return -1; }
			if (GetTime(time) < 0) { return -1; }
			return 0;
		}

		/// <summary>Split a string by a delimiter</summary>
		/// <param name="str"> -[in]- String to be slit.</param>
		/// <param name="delimiter"> -[in]- Delimiter to find.</param>
		/// <returns>A std::vector of std::strings containing the parsed segments.</returns>
		static std::vector<std::string> SplitString(std::string str, char delimiter)
		{
			std::stringstream ss(str);					// Use the string in a stringstream
			std::vector<std::string> results;			// Vector to store parse results
			std::string token;							// String to store a parsed segment
			while (std::getline(ss, token, delimiter))	// While there is data in the ss, parse it and store into token
			{
				results.push_back(token);				// Push token onto vector
			}
			return results;								// return vector of results. 
		}

		/// <summary>Removes spaces from a string</summary>
		/// <param name="str"> -[in/out]- A string to remove spaces from.</param>
		static void RemoveStringSpaces(std::string& str)
		{
			str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
		}

		/// <summary>Encrypts a license structure into a license file</summary>
		/// <param name="license"> -[in]- License to be encrypted.</param>
		/// <param name="filePath"> -[in]- File path and name to write to. 
		/// License extension will be appended.</param>
		/// <returns>True = successful, False = failure.
		/// Call GetLastError to know more.</returns>
		static bool Encrypt(License license, std::string filePath)
		{
			// Default return
			return false;
		}

		/// <summary>Decrypts a license file into a license structure</summary>
		/// <param name="license"> -[out]- License to decrypt into.</param>
		/// <param name="filePath"> -[in]- File path and name to the license.</param>
		/// <returns>True = successful, False = failure.
		/// Call GetLastError to know more.</returns>
		static bool Decrypt(License license, std::string filePath)
		{
			// Default return
			return false;
		}
	}
}