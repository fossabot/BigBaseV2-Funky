#include "common.hpp"
#include "JavascriptTesting.hpp"


void big::JavaScriptTesting::BeginContext()
{
	memset(this->chakra.jsResult, 0, sizeof(this->chakra.jsResult));

	JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &chakra.runtime);

	JsCreateContext(chakra.runtime, &chakra.context);

	JsSetCurrentContext(chakra.context);

	g_Logger->Info("Allocated JavaScript Runtime");
}

void big::JavaScriptTesting::CopyInput(char* _input)
{
	


	size_t strLen = strlen(_input);

	this->input = (wchar_t*)malloc((strLen + 1) * sizeof(wchar_t));
	memset(this->input, 0, (strLen + 1) * sizeof(wchar_t));

	mbstowcs(this->input, _input, strLen + 1);
}

void big::JavaScriptTesting::RunScript()
{
	JsRunScript(this->input, chakra.currentSourceContext++, L"", &chakra.result);

	JsValueRef resultJSString;
	JsConvertValueToString(chakra.result, &resultJSString);

	const wchar_t* resultWC;
	size_t stringLength;
	JsStringToPointer(resultJSString, &resultWC, &stringLength);

	// its a bit unsafe ik ik
	wcstombs(this->chakra.jsResult, resultWC, stringLength);

	
}

void big::JavaScriptTesting::EndContext()
{
	free(this->input);

	JsSetCurrentContext(JS_INVALID_REFERENCE);
	JsDisposeRuntime(chakra.runtime);
}
