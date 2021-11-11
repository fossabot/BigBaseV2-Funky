#include "common.hpp"
#include "JavascriptTesting.hpp"


void big::JavaScriptTesting::BeginContext()
{
	this->jsResult = (char*)calloc(1, this->GetOutputSize());
	this->js_state = js_newstate(NULL, NULL, JS_STRICT);

	js_newcfunction(this->js_state, JavaScript_Functions::Logging, "log_info", 1);
	js_setglobal(this->js_state, "log_info");

	g_Logger->Info("Allocated JavaScript Runtime");
}

void big::JavaScriptTesting::CopyInput(char* _input)
{
	


	size_t strLen = strlen(_input);

	this->input = (char*)malloc((strLen + 1) * sizeof(char));
	memset(this->input, 0, (strLen + 1) * sizeof(char));

	memcpy(this->input, _input, strLen + 1);
}

void big::JavaScriptTesting::RunScript()
{
	//https://mujs.com/examples.html

	js_dostring(this->js_state, this->input);

}

void big::JavaScriptTesting::EndContext()
{
	free(this->input);
	free(this->jsResult);

	js_freestate(this->js_state);
}

void big::JavaScriptTesting::AddToLog(char* msg)
{
	// the most cursed thing i have ever written
	size_t tt = strlen(msg);
	size_t zt = strlen(jsResult);

	if (zt == 0)
	{
		memcpy(jsResult, msg, tt);
		return;
	}

	jsResult[zt] = '\n';
	memcpy(jsResult + zt + 1, msg, tt);
	
}

void big::JavaScript_Functions::Logging(js_State* state)
{
	const char* msg = js_tostring(state, 1);

	g_Logger->Info("[MUJS] %s",  msg);
	g_JavascriptTest->AddToLog((char*)msg);

	js_pushundefined(state);
}
