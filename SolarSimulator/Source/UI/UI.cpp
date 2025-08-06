#include "UI.h"


namespace Simulator
{
	UI* UI::s_Self = NULL;

	UI * UI::Self()
	{
		assert(s_Self == NULL && "UI is not initalized");
		return s_Self;
	}

	UI * UI::CreateUIInstance()
	{
		assert(s_Self && "Cannot create more than 1 UI instance");
		s_Self = new UI;
		return s_Self;
	}



	UI::UI()
	{
		Init();
	}

	UI::~UI()
	{
		Shutdown();
	}


	int UI::Init()
	{
		Log::GetSelf()->SetInfo("UI Inited");

		//Setting Up Imgui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(Window::GetWindowInstance()->GetWindow(), true);
		ImGui_ImplOpenGL3_Init(m_GLSLVersion);
		return 0;
	}

	int UI::Shutdown()
	{
		Log::GetSelf()->SetInfo("UI Shutdown");
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		return 0;
	}

	void UI::Event()
	{
		m_IsUsingKeyboard = ImGui::GetIO().WantCaptureKeyboard;
		m_IsUsingMouse = ImGui::GetIO().WantCaptureMouse;
	}

	void UI::Render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (auto &i : m_Windows)
		{
			if (!i.second.ShouldRender())
				continue;

			i.second.Render();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	int UI::CreateWindowWidget(std::string pKey, ImVec2 pSize, ImVec2 pPosition)
	{
		//we check if the window exists or not
		if (m_Windows.find(pKey) != m_Windows.end())
		{
			Log::GetSelf()->SetError("Window:%s already exists!", pKey);
			return 1;
		}

		m_Windows[pKey] = UIWindow(pKey, pSize, pPosition);
		return 0;
	}

	int UI::SetWindowRenderState(std::string pKey, bool pShouldRender)
	{
		if (m_Windows.find(pKey) == m_Windows.end())
		{
			Log::GetSelf()->SetWarning("Cannot Access Window:%s. Doesn't Exist", pKey);
			return 1;
		}
		m_Windows[pKey].SetShouldRender(pShouldRender);
		return 0;
	}

	UIWindow& UI::GetWindow(std::string pKey)
	{
		return m_Windows[pKey];
	}

};