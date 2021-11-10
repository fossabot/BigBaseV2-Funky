# BigBaseV2 but funky
A mod menu base for Grand Theft Auto V.
Strictly for educational purposes.

## Features
* ImGui–based user interface
* Unloading at runtime
* Log console
* Script fibers
* Fiber pool
* Access to YSC script globals
* scrProgram–based native hook

## Building
To build BigBaseV2 you need:
* Visual Studio 2019
* [Premake 5.0](https://premake.github.io/download.html) in your PATH

To set up the build environment, run the following commands in a terminal:
```dos
git clone https://github.com/PatchByte/BigBaseV2-Funky.git --recurse-submodules
cd BigBaseV2-Funky
premake5 vs2019
```
Now, you will be able to open the solution, and simply build it in Visual Studio.



# Getting a error at mujs?

```c
static int js_ptry(js_State *J) {
	if (J->trytop == JS_TRYLIMIT) {
		STACK[TOP].type = JS_TLITSTR;
		STACK[TOP].u.litstr = "exception stack overflow";
		TOP;
		return 1;
	}
	return 0;
}
```
change it to
```c
static int js_ptry(js_State *J) {
	if (J->trytop == JS_TRYLIMIT) {
		J->stack[J->top].type = JS_TLITSTR;
		J->stack[J->top].u.litstr = "exception stack overflow";
		++J->top;
		return 1;
	}
	return 0;
}
```


# What now?
### **And please for the sake build into release mode!**