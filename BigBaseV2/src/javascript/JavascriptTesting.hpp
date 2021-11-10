#pragma once
#include "../common.hpp"
#include <mujs.h>

namespace big
{
	struct JavaScript_ChakraRuntime
	{
		unsigned currentSourceContext = 0;

		char *jsResult =  0 ;
	};

	class JavaScriptTesting
	{
	private:
		JavaScript_ChakraRuntime chakra;

	public:
		void BeginContext();
		void CopyInput(char* _input);
		void RunScript();
		size_t GetOutputSize() { return 128; }
		char* GetOutput() { return chakra.jsResult; }

		void EndContext();

	private:
		
		wchar_t *input = nullptr;
	};

	inline std::unique_ptr<JavaScriptTesting> g_JavascriptTest;
}