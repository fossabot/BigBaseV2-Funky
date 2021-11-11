#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta/joaat.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script.hpp"
#include "javascript/JavascriptTesting.hpp"

#include <imgui.h>

namespace big
{
	void gui::dx_init()
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.14f, 0.16f, 0.11f, 0.52f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27f, 0.30f, 0.23f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.29f, 0.34f, 0.26f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.28f, 0.32f, 0.24f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.30f, 0.22f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.23f, 0.27f, 0.21f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_Button] = ImVec4(0.29f, 0.34f, 0.26f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_Header] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.42f, 0.31f, 0.6f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.54f, 0.57f, 0.51f, 0.50f);
		colors[ImGuiCol_Separator] = ImVec4(0.14f, 0.16f, 0.11f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.19f, 0.23f, 0.18f, 0.00f); // grip invis
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.54f, 0.57f, 0.51f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_Tab] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.54f, 0.57f, 0.51f, 0.78f);
		colors[ImGuiCol_TabActive] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.24f, 0.27f, 0.20f, 1.00f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.42f, 0.31f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.78f, 0.28f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(0.73f, 0.67f, 0.24f, 1.00f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.59f, 0.54f, 0.18f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

		ImGuiStyle& style = ImGui::GetStyle();
		style.FrameBorderSize = 1.0f;
		style.WindowRounding = 0.0f;
		style.ChildRounding = 0.0f;
		style.FrameRounding = 0.0f;
		style.PopupRounding = 0.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabRounding = 0.0f;
		style.TabRounding = 0.0f;
		style.TabBorderSize = 1.0f;
	}

	void gui::dx_on_tick()
	{
		if (ImGui::Begin("BigBaseV2"))
		{
			ImGui::BeginTabBar("##Main_Tab_Bar");
			if (ImGui::BeginTabItem("Test"))
			{
				
				static bool demo_bool = true;
				static int demo_int = 1;
				static float demo_float = 1.f;

				static const char* demo_combo[]
				{
					"One",
					"Two",
					"Three"
				};
				static int demo_combo_pos = 0;

				ImGui::Checkbox("Bool", &demo_bool);
				ImGui::SliderInt("Int", &demo_int, 0, 10);
				ImGui::SliderFloat("Float", &demo_float, 0.f, 10.f);
				ImGui::Combo("Combo", &demo_combo_pos, demo_combo, sizeof(demo_combo) / sizeof(*demo_combo));
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Vehicle"))
			{
				if (ImGui::Button("Spawn a vehicle"))
				{
					g_fiber_pool->queue_job([]
						{
							auto hash = rage::joaat("adder");
							while (!STREAMING::HAS_MODEL_LOADED(hash))
							{
								STREAMING::REQUEST_MODEL(hash);
								script::get_current()->yield();
							}

							auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
							auto vehicle = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, 0.f, true, true);

							if (*g_pointers->m_is_session_started)
							{
								DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
							}

							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
						});
				}
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("JS"))
			{
				static char input[1024] = { 0 };
				static char output[1024] = { 0 };


				ImGui::InputTextMultiline("##output_js", output, sizeof(output), ImVec2(-1, 250), ImGuiInputTextFlags_ReadOnly);
				ImGui::InputTextMultiline("##input_js", input, sizeof(input), ImVec2(-1, 250));
				if (ImGui::Button("Run Script"))
				{
					g_JavascriptTest->BeginContext(); // ALLOCATION
					g_JavascriptTest->CopyInput(input); // COPY INPUT
					g_JavascriptTest->RunScript(); // RIM

					{ // COPY RESULT
						memset(output, 0, sizeof(output));
						memcpy(output, g_JavascriptTest->GetOutput(), g_JavascriptTest->GetOutputSize());
					}

					g_JavascriptTest->EndContext(); // DEALLOCATING
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Settings"))
			{
				if (ImGui::Button("Unload"))
				{
					g_running = false;
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}

	void gui::script_init()
	{
	}

	void gui::script_on_tick()
	{
		if (g_gui.m_opened)
		{
			CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(0);
		}
	}

	void gui::script_func()
	{
		g_gui.script_init();
		while (true)
		{
			g_gui.script_on_tick();
			script::get_current()->yield();
		}
	}
}
