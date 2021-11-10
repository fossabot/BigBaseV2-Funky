#pragma once

namespace big
{
	class detour_hook
	{
	public:
		explicit detour_hook(const char* name, void *target, void *detour);
		~detour_hook() noexcept;

		detour_hook(detour_hook&& that) = delete;
		detour_hook& operator=(detour_hook&& that) = delete;
		detour_hook(detour_hook const&) = delete;
		detour_hook& operator=(detour_hook const&) = delete;


		template <typename T>
		T get_original();

	private:
		std::uint32_t m_hash;
		void *m_target;
		void *m_detour;
		void *m_original{};
	};

	template <typename T>
	inline T detour_hook::get_original()
	{
		return static_cast<T>(m_original);
	}
}
