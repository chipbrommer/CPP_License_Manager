#pragma once

#ifdef _WIN32
#include <stdint.h>		// standard integers
#endif

#include <iostream>

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

		protected:
		private:
		};
	}
}