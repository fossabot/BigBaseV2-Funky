#include "common.hpp"
#include "logger.hpp"
#include "pointers.hpp"
#include "Memory.hpp"

namespace big
{
	pointers::pointers()
	{


		m_swapchain = Signature("ff 50 60 44 39 30 74 6a").Scan().Add(8).Add(3).Rip().As<IDXGISwapChain**>();
		m_script_globals = Signature("48 8D 15 ? ? ? ? 4C 8B C0 E8 ? ? ? ? 48 85 FF 48 89 1D").Scan().Add(3).Rip().As<std::int64_t**>();
		m_script_program_table = Signature("44 8B 0D ? ? ? ? 4C 8B 1D ? ? ? ? 48 8B 1D ? ? ? ? 41 83 F8 FF 74 3F 49 63 C0 42 0F B6 0C 18 81 E1").Scan().Add(17).Rip().As<rage::scrProgramTable*>();
		m_fix_vectors = Signature("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA").Scan().As<decltype(m_fix_vectors)>();

		{
			MemoryHandle temp = Signature("45 33 F6 8B E9 85 C9 B8").Scan();

			m_run_script_threads = temp.Sub(0x1F).As<functions::run_script_threads_t>();
			m_script_threads = temp.Sub(4).Rip().Sub(8).As<decltype(m_script_threads)>();
		}

		{
			MemoryHandle temp = Signature("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A").Scan();

			m_native_registration_table = temp.Add(3).Rip().As<rage::scrNativeRegistrationTable*>();
			m_get_native_handler = temp.Add(12).Rip().As<functions::get_native_handler_t>();
		}

		m_ped_factory = Signature("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81").Scan().Add(3).Rip().As<CPedFactory**>();
		m_is_session_started = Signature("40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE").Scan().Add(3).Rip().As<bool*>();
		m_model_bypass = Signature("40 53 48 83 ec 20 e8 ? ? ? ? 48 8b d8 48 85 c0 74 12").Scan().Add(0x1E).As<PVOID>();

		m_hwnd = FindWindowW(L"grcWindow", nullptr);
		if (!m_hwnd)
			throw std::runtime_error("Failed to find the game's window.");

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}
