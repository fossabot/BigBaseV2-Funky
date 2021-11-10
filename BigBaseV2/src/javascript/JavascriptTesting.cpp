#include "common.hpp"
#include "JavascriptTesting.hpp"


void big::JavaScriptTesting::BeginContext()
{
	this->chakra.jsResult = (char*)calloc(1, this->GetOutputSize());
	this->chakra.js_state = js_newstate(NULL, NULL, JS_STRICT);


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

	js_freestate(this->chakra.js_state);
}

void big::JavaScript_Functions::Logging(js_State* state)
{
	const char* msg = js_tostring(state, 1);

	g_Logger->Info("[MUJS] %s",  msg);

	js_pushundefined(state);
}
