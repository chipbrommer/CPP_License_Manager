#pragma once

#ifdef _WIN32
#include <stdint.h>		// standard integers
#endif

#include <iostream>		// console out
#include <fstream>		// File input
#include <format>		// C++ string formats for C++20 and up
#include <vector>
#include "License_Manager_Info.h"
#include <stdio.h>
#include <Windows.h>
#include <iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")

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
		/// <param name="str"> -[in|out]- A string to remove spaces from.</param>
		static void RemoveStringSpaces(std::string& str)
		{
			str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
		}

		/// <summary>Parses a license txt file into a License structure.</summary>
		/// <param name="licenseFile"> -[in]- Reference to a file stream to the file.</param>
		/// <param name="license"> -[out]- Reference to a License structure to store the data into.</param>
		/// <returns>-1 on fail. 0 on success.</returns>
		static int8_t ParseLicenseTextFileToStruct(std::fstream& licenseFile, License& license)
		{
			if (!licenseFile.is_open())
			{
				return -1;
			}

			std::string line;
			while (std::getline(licenseFile, line))
			{
				RemoveStringSpaces(line);

				std::vector<std::string> results = SplitString(line, '=');

				// Find the start date
				if (results[0] == "STARTDATE")
				{
					for (uint8_t i = 0; i < sizeof(LM_Delimiters); i++)
					{
						std::vector<std::string> dates = SplitString(results[1], LM_Delimiters[i]);

						// When we find a proper date, parse it into the startDate var and exit the for loop/ 
						if (dates.size() == 3)
						{
							license.startDate.setDates((uint8_t)std::stoi(dates[0]), (uint8_t)std::stoi(dates[1]), (uint16_t)std::stoi(dates[2]));
							break;
						}
					}
				}

				// Find the end date
				if (results[0] == "ENDDATE")
				{
					for (uint8_t i = 0; i < sizeof(LM_Delimiters); i++)
					{
						std::vector<std::string> dates = SplitString(results[1], LM_Delimiters[i]);

						// When we find a proper date, parse it into the endDate var and exit the for loop/ 
						if (dates.size() == 3)
						{
							license.endDate.setDates((uint8_t)std::stoi(dates[0]), (uint8_t)std::stoi(dates[1]), (uint16_t)std::stoi(dates[2]));
							break;
						}
					}
				}
			}

			// Default return
			return 0;
		}

		/// <summary>Get the MAC Address and IP Address of the main ethernet adapter.</summary>
		/// <param name="mac"> -[out]- reference to an std::string to store mac address into</param>
		/// <param name="ip"> -[out]- reference to an std::string to store ip address into</param>
		/// <returns>-1 on fail. 0 on success.</returns>
		static int8_t GetEthernetAdapterInformation(std::string& mac, std::string& ip)
		{
			DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
			PIP_ADAPTER_INFO AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));

			if (AdapterInfo == NULL) 
			{
				mac = "";
				return -1;
			}

			// Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
			if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW) 
			{
				free(AdapterInfo);
				AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);

				if (AdapterInfo == NULL) 
				{
					mac = "";
					return -1;
				}
			}

			// Successfully grabbed adapter info.
			if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR) 
			{
				// Contains pointer to current adapter info
				PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;

				// Process if good data. 
				if (pAdapterInfo)
				{
					// Verify we have a good MAC address and then grab it. 
					if (pAdapterInfo->AddressLength >= 6)
					{
						mac = std::format("{:02X}:{:02X}:{:02X}:{:02X}:{:02X}:{:02X}", 
									pAdapterInfo->Address[0], pAdapterInfo->Address[1],
									pAdapterInfo->Address[2], pAdapterInfo->Address[3],
									pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
					}

					ip = pAdapterInfo->IpAddressList.IpAddress.String;
				}
			}

			free(AdapterInfo);
			return 0;
		}

		/// <summary>Get the main system volumn serial number.</summary>
		/// <param name="serialNum"> -[out]- reference to an std::string to store serial into</param>
		/// <returns>-1 on fail. 0 on success.</returns>
		static int8_t DisplayVolumeInformations(std::string& serialNum)
		{
			// Attempt to get the volume information
			DWORD VolumeSerialNumber = 0;
			GetVolumeInformation((LPCSTR)"c:\\", NULL, NULL, &VolumeSerialNumber, NULL, NULL, NULL, NULL);

			// Process if good data and return success
			if (VolumeSerialNumber)
			{
				serialNum = std::format("{:04X}{:04X}", HIWORD(VolumeSerialNumber), LOWORD(VolumeSerialNumber));
				return 0;
			}

			// Default return
			return -1;
		}

		/// <summary>Encrypts a license structure into a license file</summary>
		/// <param name="license"> -[in]- License to be encrypted.</param>
		/// <param name="filePath"> -[in]- File path and name to write to. 
		/// License extension will be appended.</param>
		/// <returns>-1 on fail. 0 on success.</returns>
		static int8_t Encrypt(License license, std::string filePath)
		{
			// Default return
			return 0;
		}

		/// <summary>Decrypts a license file into a license structure</summary>
		/// <param name="license"> -[out]- License to decrypt into.</param>
		/// <param name="filePath"> -[in]- File path and name to the license.</param>
		/// <returns>-1 on fail. 0 on success.</returns>
		static int8_t Decrypt(License license, std::string filePath)
		{
			// Default return
			return 0;
		}
	
		static int8_t WriteLicense(std::fstream& fileOut, License& license)
		{
			if (!fileOut.is_open())
			{
				return -1;
			}

			fileOut << license.toString();

			// TODO Write out data as encrypted. 

			return 0;
		}
	}
}


//static char* GetMacAddress()
//{
//	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);
//	char* mac_addr = (char*)malloc(18);
//	PIP_ADAPTER_INFO AdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
//
//	if (AdapterInfo == NULL)
//	{
//		free(mac_addr);
//		return NULL; // it is safe to call free(NULL)
//	}
//
//	// Make an initial call to GetAdaptersInfo to get the necessary size into the dwBufLen variable
//	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW)
//	{
//		free(AdapterInfo);
//		AdapterInfo = (IP_ADAPTER_INFO*)malloc(dwBufLen);
//
//		if (AdapterInfo == NULL)
//		{
//			free(mac_addr);
//			return NULL;
//		}
//	}
//
//	if (GetAdaptersInfo(AdapterInfo, &dwBufLen) == NO_ERROR)
//	{
//		// Contains pointer to current adapter info
//		PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
//		//do {
//		//	// technically should look at pAdapterInfo->AddressLength and not assume it is 6.
//		//	if (pAdapterInfo->AddressLength >= 6)
//		//	{
//		//		sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
//		//			pAdapterInfo->Address[0], pAdapterInfo->Address[1],
//		//			pAdapterInfo->Address[2], pAdapterInfo->Address[3],
//		//			pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
//		//	}
//
//		//	printf("Address: %s, mac: %s\n", pAdapterInfo->IpAddressList.IpAddress.String, mac_addr);
//		//	// print them all, return the last one.
//		//	// return mac_addr;
//
//		//	pAdapterInfo = pAdapterInfo->Next;
//		//} while (pAdapterInfo);
//
//		if (pAdapterInfo)
//		{
//			if (pAdapterInfo->AddressLength >= 6)
//			{
//				sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X",
//					pAdapterInfo->Address[0], pAdapterInfo->Address[1],
//					pAdapterInfo->Address[2], pAdapterInfo->Address[3],
//					pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
//
//				std::string temp = std::string(std::format("Hello {}", 1));
//
//			}
//
//			printf("Address: %s, mac: %s\n", pAdapterInfo->IpAddressList.IpAddress.String, mac_addr);
//		}
//	}
//
//	free(AdapterInfo);
//	return mac_addr;
//}