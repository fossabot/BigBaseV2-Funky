#pragma once
#include "../common.hpp"
#include <mujs.h>

namespace big
{


	struct JavaScript_Functions
	{
		static void Logging(js_State* state);
	};

	class JavaScriptTesting
	{
	private:
		js_State* js_state;
		char* jsResult = 0;
	public:
		void BeginContext();
		void CopyInput(char* _input);
		void RunScript();
		size_t GetOutputSize() { return 128; }
		char* GetOutput() { return jsResult; }

		void EndContext();

		void AddToLog(char* msg);

	private:
		
		char *input = nullptr;
	};

	inline std::unique_ptr<JavaScriptTesting> g_JavascriptTest;
}