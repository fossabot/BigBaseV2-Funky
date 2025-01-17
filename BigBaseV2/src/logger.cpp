#include "logger.hpp"
#include "common.hpp"

namespace big
{

	void log::initialize()
	{
		/*basic console stuff*/
		{
			AllocConsole();
			SetConsoleTitleA("Patchendesbyte");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			SetConsoleCP(CP_UTF8);
			SetConsoleOutputCP(CP_UTF8);

		}

		this->m_Output.open("CONOUT$");
		this->m_Input.open("CONIN$");
		auto m_P = big::g_cheat_directory; m_P /= "log.txt";
		this->m_FileOutput.open(m_P, std::ios::trunc);

	}

	void log::shutdown()
	{

		FreeConsole();
	}

	void log::Info(const char* format, ...)
	{

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		std::va_list args{};
		va_start(args, format);
		Log("Info", format, args);
		va_end(args);
	}

	void log::Error(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::va_list args{};
		va_start(args, format);
		Log("Info", format, args);

		va_end(args);
	}

	void log::Warning(const char* format, ...)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
		std::va_list args{};
		va_start(args, format);
		Log("Warning", format, args);
		va_end(args);
	}

	void log::Log(const char* type, const char* format, std::va_list args)
	{

		auto time = std::time(nullptr);
		auto tm = std::localtime(&time);

		char prefix[64] = {};
		std::snprintf(prefix, sizeof(prefix) - 1, "[%02d:%02d:%02d] [%s] ", tm->tm_hour, tm->tm_min, tm->tm_sec, type);

		std::size_t messageLength = std::vsnprintf(nullptr, 0, format, args) + 1;
		auto messageBuffer = std::make_unique<char[]>(messageLength);

		std::uninitialized_fill_n(messageBuffer.get(), messageLength, '\0');
		std::vsnprintf(messageBuffer.get(), messageLength, format, args);

		this->m_Output << prefix << messageBuffer.get() << std::endl;
		this->m_FileOutput << prefix << messageBuffer.get() << std::endl;

		messageBuffer.reset();
	}


}