#include <stdint.h>
#include <map>
#include <string>
#include <ctime>
#include <format>
#include <sstream>

#ifdef _WIN32
#include	<windows.h>					// Windows necessary stuff
#include	<direct.h>					// Make Directory
#endif

namespace Essentials
{
	namespace CPP_License_Manager
	{
		constexpr static uint8_t VERSION_MAJOR = 0;
		constexpr static uint8_t VERSION_MINOR = 1;
		constexpr static uint8_t VERSION_PATCH = 0;
		constexpr static uint8_t VERSION_BUILD = 0;

		constexpr static char licenseExtension[] = ".lic";

		/// <summary>Enum class for the available tool errors. </summary>
		enum class LM_ERROR : uint8_t
		{
			NO_LM_ERROR,
			MANAGER_INFO_NOT_SET,
			START_DATE_NOT_SET,
			END_DATE_NOT_SET,
			ISSUE_DATE_NOT_SET,
			ISSUE_TIME_NOT_SET,
			ISSUER_INFO_NOT_SET,
			FILE_OPEN_ERROR,
			FILE_CLOSE_ERROR,
			LICENSE_OPEN_ERROR,
			LICENSE_CLOSE_ERROR,
			LICENSE_EXPIRED,
			LICENSE_PREDATED,
		};

		/// <summary>A Map to convert an error value to a readable string.</summary>
		static std::map<LM_ERROR, std::string> ErrorMap
		{
			{LM_ERROR::NO_LM_ERROR,			std::format("Error Code {} - No error.\n",							(uint8_t)LM_ERROR::NO_LM_ERROR)},
			{LM_ERROR::MANAGER_INFO_NOT_SET,std::format("Error Code {} - License Manager info is not set.\n",	(uint8_t)LM_ERROR::MANAGER_INFO_NOT_SET)},
			{LM_ERROR::START_DATE_NOT_SET,	std::format("Error Code {} - Start date is not set.\n",				(uint8_t)LM_ERROR::START_DATE_NOT_SET)},
			{LM_ERROR::END_DATE_NOT_SET,	std::format("Error Code {} - End date is not set.\n",				(uint8_t)LM_ERROR::END_DATE_NOT_SET)},
			{LM_ERROR::ISSUE_DATE_NOT_SET,	std::format("Error Code {} - Issue date is not set.\n",				(uint8_t)LM_ERROR::ISSUE_DATE_NOT_SET)},
			{LM_ERROR::ISSUE_TIME_NOT_SET,	std::format("Error Code {} - Issue time is not set.\n",				(uint8_t)LM_ERROR::ISSUE_TIME_NOT_SET)},
			{LM_ERROR::ISSUER_INFO_NOT_SET,	std::format("Error Code {} - Issuer information is not set.\n",		(uint8_t)LM_ERROR::ISSUER_INFO_NOT_SET)},
			{LM_ERROR::FILE_OPEN_ERROR,		std::format("Error Code {} - Failed to open file.\n",				(uint8_t)LM_ERROR::FILE_OPEN_ERROR)},
			{LM_ERROR::FILE_CLOSE_ERROR,	std::format("Error Code {} - Failed to close file.\n",				(uint8_t)LM_ERROR::FILE_CLOSE_ERROR)},
			{LM_ERROR::LICENSE_OPEN_ERROR,	std::format("Error Code {} - Failed to open license.\n",			(uint8_t)LM_ERROR::LICENSE_OPEN_ERROR)},
			{LM_ERROR::LICENSE_CLOSE_ERROR,	std::format("Error Code {} - Failed to close license.\n",			(uint8_t)LM_ERROR::LICENSE_CLOSE_ERROR)},
			{LM_ERROR::LICENSE_EXPIRED,		std::format("Error Code {} - Failed to open license.\n",			(uint8_t)LM_ERROR::LICENSE_EXPIRED)},
			{LM_ERROR::LICENSE_PREDATED,	std::format("Error Code {} - Failed to close license.\n",			(uint8_t)LM_ERROR::LICENSE_PREDATED)},
		};

		static char LM_Delimiters[] = { '-','/','\\',':' };

		/// <summary>A data structure to hold License Manager tool information.</summary>
		struct Manager
		{
			uint8_t versionMajor = 0;
			uint8_t versionMinor = 0;

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return versionMajor != 0 || versionMinor != 0;
			}

			/// <summary>Gets the manager data in string format</summary>
			/// <returns>A string containing the manager version data</returns>
			std::string toString()
			{
				return std::format("{}.{}", versionMajor, versionMinor);
			}

			/// <summary>Sets the data for the struct</summary>
			/// <returns>0 on success, -1 on fail</returns>
			uint8_t setVersion(uint8_t major, uint8_t minor)
			{
				versionMajor = major;
				versionMinor = minor;

				if (!isSet())
				{
					return -1;
				}

				return 0;
			}
		};

		/// <summary>A data structure to hold a date</summary>
		struct Date
		{
			uint8_t month = 0;
			uint8_t day = 0;
			uint16_t year = 0;

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return month != 0 && day != 0 && year != 0;
			}

			/// <summary>Gets the date in string format</summary>
			/// <returns>A string containing the date {MM/DD/YYY}</returns>
			std::string toString()
			{
				return std::format("{}/{}/{}", month, day, year);
			}

			void setDates(uint8_t m, uint8_t d, uint16_t y)
			{
				month = m;
				day = d;
				year = y;
			}

			// Check if two Date objects are equal
			bool operator== (Date const& rhs) const 
			{
				return	this->month	== rhs.month	&&
						this->day	== rhs.day		&&
						this->year	== rhs.year;
			}

			// Check if a left hand side date is past a right hand side date. 
			bool operator>= (Date const& rhs) const
			{
				if (this->year > rhs.year) { return true; }
				if (this->month > rhs.month && this->year == rhs.year) { return true; }
				if (this->day >= rhs.day	&& this->month == rhs.month && this->year == rhs.year) { return true; }
			
				return false;
			}
		};

		/// <summary>A data structure to hold time</summary>
		struct Time
		{
			uint8_t hour = 0;
			uint8_t minute = 0;
			uint8_t second = 0;

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return hour != 0 && minute != 0 && second != 0;
			}

			/// <summary>Gets the time in string format</summary>
			/// <returns>A string containing the time {HR:MIN:SECS}</returns>
			std::string toString()
			{
				return std::format("{}:{}:{}", hour, minute, second);
			}

			void setTime(uint8_t h, uint8_t m, uint8_t s)
			{
				hour = h;
				minute = m;
				second = s;
			}

			// Check if two Time objects are equal
			bool operator== (Time const& rhs) const
			{
				return	this->hour		== rhs.hour		&&
						this->minute	== rhs.minute	&&
						this->second	== rhs.second;
			}

			// Check if a left hand side time is past a right hand side time. 
			bool operator>= (Time const& rhs) const
			{
				if (this->hour > rhs.hour) { return true; }
				if (this->minute > rhs.minute	&& this->hour == rhs.hour) { return true; }
				if (this->second >= rhs.second	&& this->minute == rhs.minute && this->hour == rhs.hour) { return true; }

				return false;
			}
		};

		/// <summary>A data structure to hold hardware information</summary>
		struct Hardware
		{
			char	userMacAddress[6] = {'\0'};

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return strcmp(userMacAddress, "") != 0 && userMacAddress[0] != '\0';
			}

			/// <summary>Gets the hardware information</summary>
			/// <returns>A string containing the hardware information</returns>
			std::string macAddressToString()
			{
				if (!isSet())
				{
					return "NOT SET!";
				}

				return std::format("{}:{}:{}:{}:{}:{}", userMacAddress[0], userMacAddress[1], 
														userMacAddress[2], userMacAddress[3], 
														userMacAddress[4], userMacAddress[5]);
			}

			/// <summary>Display the hardware information to console</summary>
			void display()
			{
				std::cout << std::format("Hardware:\n");
				std::cout << std::format("\tMAC Address: {}\n", macAddressToString());
			}
		};

		/// <summary>A data structure to information of the license issuer</summary>
		struct Issuer
		{
			uint8_t id = 0;
			char	name[20] = { '\0' };
			char	email[50] = { '\0' };
			Date	issueDate = {};
			Time	issueTime = {};

			/// <summary>A bool to tell if the basic needed data is populated.
			///	Thus saying the issuer is ready to be used.</summary>
			bool isReady()
			{
				return issueDate.isSet();
			}

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return	strcmp(name, "") != 0		&& name[0] != '\0'	&&
						strcmp(email, "") != 0		&& email[0] != '\0'	&&
						issueDate.isSet()			&& issueTime.isSet();
			}

			/// <summary>Display the hardware information to console</summary>
			void display()
			{
				std::cout << std::format("Issuer:\n");
				std::cout << std::format("\tID:          {}\n", id);
				std::cout << std::format("\tName:        {}\n", name);
				std::cout << std::format("\tEmail:       {}\n", email);
				std::cout << std::format("\tIssue  Date: {}\n", issueDate.toString());
				std::cout << std::format("\tIssue Time:  {}\n", issueTime.toString());
				std::cout << "\n";
			}
		};

		/// <summary>A data structure for a software license</summary>
		struct License
		{
			Manager		managerInfo = {};
			Date		startDate = {};
			Date		endDate = {};
			Hardware	hardware = {};
			Issuer		issuer = {};
			char		activationToken[24];

			/// <summary>A bool to tell if the basic needed data is populated.
			///	Thus saying the license is ready to be generated.</summary>
			bool isReady()
			{
				return	managerInfo.isSet()		&& startDate.isSet()	&&
						issuer.isReady()		&& endDate.isSet();	
			}

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return	managerInfo.isSet()	&& startDate.isSet()	&&
						endDate.isSet()		&& hardware.isSet()		&&
						issuer.isSet()		&& 
						strcmp(activationToken, "") != 0 && activationToken[0] != '\0';
			}

			/// <summary>Display the license information to console</summary>
			void display()
			{
				std::cout << std::format("License:\n");
				std::cout << std::format("\tLicense Version: {}\n", managerInfo.toString());
				std::cout << std::format("\tStart Date:      {}\n", startDate.toString());
				std::cout << std::format("\tEnd Date:        {}\n", endDate.toString());
				std::cout << std::format("Hardware:\n");
				std::cout << std::format("\tMAC Address:     {}\n", hardware.macAddressToString());
				issuer.display();
			}
		};

	}
}