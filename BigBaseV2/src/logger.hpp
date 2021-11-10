#pragma once
#include "common.hpp"
#include <cstdarg>

namespace big
{
	class log
	{
	private:
	public:
		std::ofstream m_Output;
		std::ofstream m_Input;
		std::ofstream m_FileOutput;
	public:
		log() = default;
		~log() = default;

		void initialize();
		void shutdown();

		void Info(const char* format, ...);
		void Error(const char* format, ...);
		void Warning(const char* format, ...);

		void Log(const char* type, const char* format, std::va_list args);
	};

	inline std::unique_ptr<log> g_Logger;
}
