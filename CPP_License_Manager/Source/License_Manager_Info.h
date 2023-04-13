#include <stdint.h>

namespace Essentials
{
	namespace CPP_License_Manager
	{
		constexpr static uint8_t VERSION_MAJOR = 0;
		constexpr static uint8_t VERSION_MINOR = 1;
		constexpr static uint8_t VERSION_PATCH = 0;
		constexpr static uint8_t VERSION_BUILD = 0;

		struct Manager
		{
			uint8_t versionMajor;
			uint8_t versionMinor;
		};

		struct Date
		{
			uint8_t month;
			uint8_t day;
			uint8_t year;
		};

		struct Time
		{
			uint8_t hour;
			uint8_t minute;
			uint8_t second;
		};

		struct Issuer
		{
			uint8_t id;
			char	name[20];
			Date	issueDate;
			Time	issueTime;
		};

		struct Hardware
		{
			char	userMacAddress[6];
		};

		struct License
		{
			Manager		managerInfo;
			Date		startDate;
			Date		endDate;
			Hardware	hardware;
			Issuer		issuer;
			char		activationToken[24];
		};
	}
}