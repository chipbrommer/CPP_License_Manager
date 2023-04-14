#include <stdint.h>
#include <map>
#include <string>
#include <ctime>
#include <format>

namespace Essentials
{
	namespace CPP_License_Manager
	{
		constexpr static uint8_t VERSION_MAJOR = 0;
		constexpr static uint8_t VERSION_MINOR = 1;
		constexpr static uint8_t VERSION_PATCH = 0;
		constexpr static uint8_t VERSION_BUILD = 0;

		/// <summary>Enum class for the available tool errors. </summary>
		enum class LM_ERROR : uint8_t
		{
			NO_ERROR,
			MANAGER_INFO_NOT_SET,
			START_DATE_NOT_SET,
			END_DATE_NOT_SET,
			ISSUE_DATE_NOT_SET,
			ISSUE_TIME_NOT_SET,
			ISSUER_INFO_NOT_SET
		};

		/// <summary>A Map to convert an error value to a readable string.</summary>
		static std::map<LM_ERROR, std::string> ErrorMap
		{
			{LM_ERROR::NO_ERROR,			std::format("Error Code {} - No error.\n",							(uint8_t)LM_ERROR::NO_ERROR)},
			{LM_ERROR::MANAGER_INFO_NOT_SET,std::format("Error Code {} - License Manager info is not set.\n",	(uint8_t)LM_ERROR::MANAGER_INFO_NOT_SET)},
			{LM_ERROR::START_DATE_NOT_SET,	std::format("Error Code {} - Start date is not set.\n",				(uint8_t)LM_ERROR::START_DATE_NOT_SET)},
			{LM_ERROR::END_DATE_NOT_SET,	std::format("Error Code {} - End date is not set.\n",				(uint8_t)LM_ERROR::END_DATE_NOT_SET)},
			{LM_ERROR::ISSUE_DATE_NOT_SET,	std::format("Error Code {} - Issue date is not set.\n",				(uint8_t)LM_ERROR::ISSUE_DATE_NOT_SET)},
			{LM_ERROR::ISSUE_TIME_NOT_SET,	std::format("Error Code {} - Issue time is not set.\n",				(uint8_t)LM_ERROR::ISSUE_TIME_NOT_SET)},
			{LM_ERROR::ISSUER_INFO_NOT_SET,	std::format("Error Code {} - Issuer information is not set.\n",		(uint8_t)LM_ERROR::ISSUER_INFO_NOT_SET)}
		};

		/// <summary>A data structure to hold License Manager tool information.</summary>
		struct Manager
		{
			uint8_t versionMajor = 0;
			uint8_t versionMinor = 0;

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return this->versionMajor != 0 || this->versionMinor != 0;
			}

			/// <summary>Gets the manager data in string format</summary>
			/// <returns>A string containing the manager version data</returns>
			std::string toString()
			{
				return std::format("{}.{}", this->versionMajor, this->versionMinor);
			}

			/// <summary>Sets the data for the struct</summary>
			/// <returns>0 on success, -1 on fail</returns>
			uint8_t setData(uint8_t major, uint8_t minor)
			{
				this->versionMajor = major;
				this->versionMinor = minor;

				if (!this->isSet())
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
				return this->month != 0 && this->day != 0 && this->year != 0;
			}

			/// <summary>Gets the date in string format</summary>
			/// <returns>A string containing the date {MM/DD/YYY}</returns>
			std::string toString()
			{
				return std::format("{}/{}/{}", this->month, this->day, this->year);
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
				return this->hour != 0 && this->minute != 0 && this->second != 0;
			}

			/// <summary>Gets the time in string format</summary>
			/// <returns>A string containing the time {HR:MIN:SECS}</returns>
			std::string toString()
			{
				return std::format("{}:{}:{}", this->hour, this->minute, this->second);
			}
		};

		/// <summary>A data structure to hold hardware information</summary>
		struct Hardware
		{
			char	userMacAddress[6] = {'\0'};

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return strcmp(this->userMacAddress, "") != 0 && this->userMacAddress[0] != '\0';
			}

			/// <summary>Gets the hardware information</summary>
			/// <returns>A string containing the hardware information</returns>
			std::string macAddressToString()
			{
				if (!isSet())
				{
					return "NOT SET!";
				}

				return std::format("{}:{}:{}:{}:{}:{}", this->userMacAddress[0], this->userMacAddress[1], 
														this->userMacAddress[2], this->userMacAddress[3], 
														this->userMacAddress[4], this->userMacAddress[5]);
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
				return this->issueDate.isSet();
			}

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return	strcmp(this->name, "") != 0		&& this->name[0] != '\0'	&&
						strcmp(this->email, "") != 0	&& this->email[0] != '\0'	&&
						this->issueDate.isSet()			&& this->issueTime.isSet();
			}

			/// <summary>Display the hardware information to console</summary>
			void display()
			{
				std::cout << std::format("Issuer:\n");
				std::cout << std::format("\tID:          {}\n", this->id);
				std::cout << std::format("\tName:        {}\n", this->name);
				std::cout << std::format("\tEmail:       {}\n", this->email);
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
				return	this->managerInfo.isSet()	&& this->startDate.isSet()	&&
						this->issuer.isReady()		&& this->endDate.isSet();	
			}

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return	this->managerInfo.isSet()	&& this->startDate.isSet()	&&
						this->endDate.isSet()		&& this->hardware.isSet()	&&
						this->issuer.isSet()		&& 
						strcmp(this->activationToken, "") != 0 && this->activationToken[0] != '\0';
			}

			/// <summary>Display the license information to console</summary>
			void display()
			{
				std::cout << std::format("License:\n");
				std::cout << std::format("\tLicense Version: {}\n", this->managerInfo.toString());
				std::cout << std::format("\tStart Date:      {}\n", this->startDate.toString());
				std::cout << std::format("\tEnd Date:        {}\n", this->startDate.toString());
				std::cout << std::format("Hardware:\n");
				std::cout << std::format("\tMAC Address:     {}\n", this->hardware.macAddressToString());
				issuer.display();
			}
		};

		/// <summary>Gets the current date</summary>
		/// <param name="date"> -[out]- Date structure to store date into.</param>
		/// <returns>-1 on fail. 0 on success.</returns>
		static uint8_t GetDate(Date& date)
		{
			time_t now = time(0);
			tm local_tm = {};
			localtime_s(&local_tm, &now);

			date.month = local_tm.tm_mon+1;
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
		static uint8_t GetTime(Time& t)
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
		static uint8_t GetDateAndTime(Date& date, Time& time)
		{
			if (GetDate(date) < 0) { return -1; }
			if (GetTime(time) < 0) { return -1; }
			return 0;
		}

	}
}