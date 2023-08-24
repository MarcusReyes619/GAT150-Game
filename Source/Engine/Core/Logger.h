#pragma once
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>
#include "Framework/Singleton.h"

#ifdef _DEBUG
#define INFO_LOG(message)	 { if (kiko::Logger::Instance().Log(kiko::LogLevel::Info, __FILE__, __LINE__))  {kiko::Logger::Instance()<<message<<"\n";}}
#define WARNING_LOG(message) { if(kiko::Logger::Instance().Log(kiko::LogLevel::Warning, __FILE__, __LINE__))  {kiko::Logger::Instance()<<message<<"\n";}}
#define ERROR_LOG(message)	 { if(kiko::Logger::Instance().Log(kiko::LogLevel::Error, __FILE__, __LINE__))    {kiko::Logger::Instance()<<message<<"\n";}}
#define ASSERT_LOG(condtion, message)	{if(!condtion && Logger::Instance().Log(kiko::LogLevel::Assert, __FILE__, __LINE__))   {kiko::Logger::Instance()<<message<<"\n";} assert(condtion);}
#else
#define INFO_LOG(message)
#define WARNING_LOG(message)
#define ERROR_LOG(message)
#define ASSERT_LOG(message)

#endif // _DEBUG

namespace kiko
{
	enum class LogLevel
	{
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger : public Singleton<Logger>
	{
	public:
		Logger(LogLevel logLevel = LogLevel::Info, std::ostream* ostream = &std::cout, const std::string& filename = "log.txt") :
			m_logLevel{ logLevel },
			m_ostream{ ostream } 
		{
			if(!filename.empty())m_fstream.open(filename);
		}

		bool Log(LogLevel logLevel, const std::string& filename, int line);

		template<typename T>
		Logger& operator<< (T vaule);

	private:
		LogLevel m_logLevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};



	template<typename T>
	inline Logger& Logger:: operator<<(T vaule) {
		if (m_ostream) *m_ostream << vaule;
		if (m_fstream.is_open()) {
			m_fstream << vaule;
			m_fstream.flush();
		}

		return *this;
	}

}