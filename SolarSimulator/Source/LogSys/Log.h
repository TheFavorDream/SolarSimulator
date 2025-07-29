#pragma once
#include "Core.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <stdarg.h>

namespace Simulator
{

	enum LOG_ENUM { LOG_LV0, LOG_LV1, LOG_LV2, LOG_LV3};
	enum CONSOLE_COLOR { GREEN = 2, RED=4, YELLOW=6, WHITE=7};

	class Log
	{
	public:

		 Log(std::string pFilePath=("Log.txt"));
		~Log();

		void EnableCaching(bool pEnable);
		void SetLoggingLevel(LOG_ENUM pLevel); //Defualt Level is 3 which means all log types get printed

		void DebugPrint(const std::string& pContent, char End='\n', bool Headline=true);
		void DebugPrint(const char* pContent, char End = '\n', bool Headline = true);

		void SetInfo(const char* pMessage, ...);
		void SetWarning(const char* pMessage, ...);
		void SetError(const char* pMessage, ...);

		void SetTextColor(CONSOLE_COLOR pColor);

	private:

		void WriteToFile(std::string pFormatedString);
		std::string FormatString(const char* pString, va_list plist);

	public://Scope for Static methods
		static Log* GetSelf();

	private: //Scope for private normal variables
		bool m_IsCaching = false;
		LOG_ENUM m_Level;
		std::fstream m_LogFile;
		std::string  m_FilePath;
	private: //Scope for private static variables
		static Log* s_Self;
	};
};
