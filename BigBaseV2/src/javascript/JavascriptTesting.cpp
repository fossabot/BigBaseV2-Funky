#include "common.hpp"
#include "JavascriptTesting.hpp"


void big::JavaScriptTesting::BeginContext()
{
	this->chakra.jsResult = (char*)calloc(1, this->GetOutputSize());

	g_Logger->Info("Allocated JavaScript Runtime");
}

void big::JavaScriptTesting::CopyInput(char* _input)
{
	


	size_t strLen = strlen(_input);

	this->input = (wchar_t*)malloc((strLen + 1) * sizeof(wchar_t));
	memset(this->input, 0, (strLen + 2) * sizeof(wchar_t));

	mbstowcs(this->input, _input, strLen + 1);
}

void big::JavaScriptTesting::RunScript()
{
	
}

void big::JavaScriptTesting::EndContext()
{
	free(this->input);
	free(this->chakra.jsResult);

	
}
