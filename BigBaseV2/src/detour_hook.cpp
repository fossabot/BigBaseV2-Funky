#include "common.hpp"
#include "detour_hook.hpp"
#include "logger.hpp"
#include <MinHook.h>
#include "gta/joaat.hpp"

namespace big
{
	detour_hook::detour_hook(const char* name, void *target, void *detour) :
		m_hash(rage::joaat(name)),
		m_target(target),
		m_detour(detour)
	{
		MH_CreateHook(m_target, m_detour, &m_original);
		
	}

	detour_hook::~detour_hook() noexcept
	{
		if (m_target)
		{
			MH_RemoveHook(m_target);
		}

		//LOG_INFO("Removed hook '{}',", m_hash);
	}


	DWORD exp_handler(PEXCEPTION_POINTERS exp, std::string const &name)
	{
		return exp->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION
			? EXCEPTION_EXECUTE_HANDLER
			: EXCEPTION_CONTINUE_SEARCH;
	}

}
