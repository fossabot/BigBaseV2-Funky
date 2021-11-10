#pragma once
#include <intrin.h>
#include "fwddec.hpp"

namespace rage
{
    class tlsContext
    {
    public:

        scrThread * *GetScriptThread()
        {
            return (scrThread**)((DWORD64)this + 0x828);
        }

        bool* IsScriptThreadActive()
        {
            return (bool*)((DWORD64)this + 0x830);
        }

        static tlsContext * get()
        {
            return *reinterpret_cast<tlsContext**>(__readgsqword(0x58));
        }
    };
}
