#include "common.hpp"
#include "crossmap.hpp"
#include "invoker.hpp"
#include "logger.hpp"
#include "pointers.hpp"

namespace big
{
	native_call_context::native_call_context()
	{
		m_return_value = &m_return_stack[0];
		m_args = &m_arg_stack[0];
	}

	void native_invoker::cache_handlers()
	{
		for (const rage::scrNativeMapping &mapping : g_crossmap)
		{
			rage::scrNativeHandler handler = g_pointers->m_get_native_handler(
				g_pointers->m_native_registration_table, mapping.second);

			m_handler_cache.emplace(mapping.first, handler);
		}
	}

	void native_invoker::begin_call()
	{
		m_call_context.reset();
	}

	void native_invoker::end_call(rage::scrNativeHash hash)
	{
		if(auto it = m_handler_cache[hash])
		{


			rage::scrNativeHandler handler = it;

			__try
			{
				handler(&m_call_context);
				g_pointers->m_fix_vectors(&m_call_context);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				g_Logger->Info("Native Handler had a exception");
			}
		}
	}

	void native_invoker::set_model_check(bool tog)
	{
		__try
		{
			if (tog == true)
			{
				*(unsigned short*)g_pointers->m_model_bypass = 0x9090;
			}
			else
			{
				*(unsigned short*)g_pointers->m_model_bypass = 0x0574;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			//LOG_INFO("Model Bypass [NULL]");
		}
	}
}
