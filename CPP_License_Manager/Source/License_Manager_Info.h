#include <stdint.h>
#include <map>
#include <string>

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
			{LM_ERROR::NO_ERROR,			"No error.\n"},
			{LM_ERROR::MANAGER_INFO_NOT_SET,"License Manager info is not set.\n"},
			{LM_ERROR::START_DATE_NOT_SET,	"Start date is not set.\n"},
			{LM_ERROR::END_DATE_NOT_SET,	"End date is not set.\n"},
			{LM_ERROR::ISSUE_DATE_NOT_SET,	"Issue date is not set.\n"},
			{LM_ERROR::ISSUE_TIME_NOT_SET,	"Issue time is not set.\n"},
			{LM_ERROR::ISSUER_INFO_NOT_SET,	"Issuer information is not set.\n"}
		};

		/// <summary>Holds the last error for the License Manager tool</summary>
		static LM_ERROR lastError = LM_ERROR::NO_ERROR;

		/// <summary>Gets the information of the lasts error in string format.</summary>
		/// <returns>String containing information about the last error.</returns>
		static std::string getLastError()
		{
			return ErrorMap[lastError];
		}

		/// <summary>A data structure to hold License Manager tool information.</summary>
		struct Manager
		{
			uint8_t versionMajor = 0;
			uint8_t versionMinor = 0;

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return this->versionMajor != 0 && this->versionMinor != 0;
			}
		};

		/// <summary>A data structure to hold a date</summary>
		struct Date
		{
			uint8_t month;
			uint8_t day;
			uint8_t year;

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return this->month != 0 && this->day != 0 && this->year != 0;
			}
		};

		/// <summary>A data structure to hold time</summary>
		struct Time
		{
			uint8_t hour;
			uint8_t minute;
			uint8_t second;

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return this->hour != 0 && this->minute != 0 && this->second != 0;
			}
		};

		/// <summary>A data structure to hold hardware information</summary>
		struct Hardware
		{
			char	userMacAddress[6] = { '\0' };

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return strcmp(this->userMacAddress, "") != 0 && this->userMacAddress[0] != '\0';
			}
		};

		/// <summary>A data structure to information of the license issuer</summary>
		struct Issuer
		{
			uint8_t id;
			char	name[20] = { '\0' };
			char	email[50] = { '\0' };
			Date	issueDate;
			Time	issueTime;

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return	strcmp(this->name, "") != 0		&& this->name[0] != '\0'	&&
						strcmp(this->email, "") != 0	&& this->email[0] != '\0'	&&
						this->issueDate.isSet()			&& this->issueTime.isSet();
			}
		};

		/// <summary>A data structure for a software license</summary>
		struct License
		{
			Manager		managerInfo;
			Date		startDate;
			Date		endDate;
			Hardware	hardware;
			Issuer		issuer;
			char		activationToken[24];

			/// <summary>A bool to tell if the basic needed data is populated.
			///	Thus saying the license is ready to be generated.</summary>
			bool isReady()
			{
				return	this->managerInfo.isSet() && this->startDate.isSet()	&&
						this->endDate.isSet();	
			}

			/// <summary>A bool to tell if ALL data is populated.</summary>
			bool isSet()
			{
				return	this->managerInfo.isSet()	&& this->startDate.isSet()	&&
						this->endDate.isSet()		&& this->hardware.isSet()	&&
						this->issuer.isSet()		&& 
						strcmp(this->activationToken, "") != 0 && this->activationToken[0] != '\0';
			}
		};
	}
}