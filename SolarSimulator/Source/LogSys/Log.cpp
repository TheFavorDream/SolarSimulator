#include "Log.h"


namespace Simulator
{
	Log* Log::s_Self = NULL;

	Log::Log(std::string pFilePath)
		: m_IsCaching(true), m_Level(LOG_LV3), m_FilePath(pFilePath)
	{
		assert(s_Self && "Instancing Log more that one!");
		if (!s_Self)
		{
			s_Self = this;
		}
		//Resets the files content
		m_LogFile.open(m_FilePath, std::ios::out);
	}

	Log::~Log()
	{
		s_Self = NULL;
	}

	void Log::EnableCaching(bool pEnable)
	{
		m_IsCaching = pEnable;
	}

	void Log::SetLoggingLevel(LOG_ENUM pLevel)
	{
		m_Level = pLevel;
	}


	void Log::DebugPrint(const std::string & pContent, char End, bool Headline)
	{
		DebugPrint(pContent.c_str(), End, Headline);
	}

	void Log::DebugPrint(const char * pContent, char End, bool Headline)
	{
		SetTextColor(GREEN);
		std::cout <<  ((Headline)? "[Debug]" : "" ) << pContent << End;
	}

	void Log::SetInfo(const char * pMessage, ...)
	{

		if (m_Level < LOG_LV3)
			return;

		va_list args;
		va_start(args, pMessage);
		std::string Str = "[Info]" + FormatString(pMessage, args) + '\n';
		va_end(args);

		WriteToFile(Str);

		SetTextColor(WHITE);
		std::cout << Str ;
	}

	void Log::SetWarning(const char * pMessage, ...)
	{

		if (m_Level < LOG_LV2)
			return;

		va_list args;
		va_start(args, pMessage);
		std::string Str = "[Warning]" + FormatString(pMessage, args) + '\n';
		va_end(args);
		WriteToFile(Str);

		SetTextColor(YELLOW);
		std::cout << Str;
	}

	void Log::SetError(const char * pMessage, ...)
	{

		if (m_Level < LOG_LV1)
			return;

		va_list args;
		va_start(args, pMessage);
		std::string Str = "[Error]" + FormatString(pMessage, args) + '\n';
		va_end(args);
		WriteToFile(Str);

		SetTextColor(RED);
		std::cout << Str;
	}

	void Log::SetTextColor(CONSOLE_COLOR pColor)
	{

#ifdef WINDOWS
		HANDLE ConsoleH = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(ConsoleH, 0<<4 | pColor);
#endif

	}

	void Log::WriteToFile(std::string pFormatedString)
	{
		if (!m_IsCaching)
			return;

		if (!m_LogFile.is_open())
		{
			m_LogFile.open(m_FilePath, std::ios::out | std::ios::app);
		}
		m_LogFile << pFormatedString;
		m_LogFile.close();
	}


	//FormatString will reformat the given string with inputs and return an String
	std::string Log::FormatString(const char * pString, va_list plist)
	{
		std::string Res;

		for (int i = 0; pString[i] != '\0'; i++)
		{
			if (pString[i] == '%')
			{
				switch (pString[i + 1])
				{
				case 'i':
					Res += std::to_string(va_arg(plist, int));
					break;
				case 'f':
					Res += std::to_string(va_arg(plist, double));
					break;
				case 'c':
					Res += va_arg(plist, const  char*);
					break; 
				case 's':
					Res += va_arg(plist, std::string);
					break;
				default:
					Res += '%';
					Res += pString[i + 1];
					break;
				}
				i++;
			}
			else
			{
				Res += pString[i];
			}
		}
		return Res;
	}

	Log * Log::GetSelf()
	{
		return s_Self;
	}
};