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


		ImGui::GetStyle().Alpha = 0.8f;
		ImGui::GetStyle().WindowRounding = 2.0f;
		ImGui::GetStyle().WindowBorderSize = 0.2f;

		return 0;
	}

	int UI::Shutdown()
	{
		Log::GetSelf()->SetInfo("UI Shutdown");
		m_Windows.clear();
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

	void UI::SetElementRenderingState(std::string pWindowKey, std::string pID, bool pState)
	{
		m_Windows[pWindowKey].GetElement(pID)->GetRenderState() = pState;
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

//======================UI Elements================================

//==============================Button=============================
	void UI::CreateButton(std::string pKey, std::string pTitle, ImVec2 pPosition, ImVec2 pSize)
	{
		m_Windows[pKey].NewElement(new Button(pTitle, pSize, pPosition));
	}
	Button* UI::GetButton(std::string pWindowKey, std::string pID)
	{
		return dynamic_cast<Button*>(m_Windows[pWindowKey].GetElement(pID));
	}
//==============================Float Slider============================

	void UI::CreateSliderF(std::string pKey, std::string pTitle, float pMax, float pMin, ImVec2 pPosition)
	{
		m_Windows[pKey].NewElement(new SliderF(pTitle, pMin, pMax, pPosition));
	}
	SliderF * UI::GetSliderF(std::string pWindowKey, std::string pID)
	{
		return dynamic_cast<SliderF*>(m_Windows[pWindowKey].GetElement(pID));
	}
//===========================Int Slider================================
	void UI::CreateSliderI(std::string pKey, std::string pTitle, int pMax, int pMin, ImVec2 pPosition)
	{
		m_Windows[pKey].NewElement(new SliderI(pTitle, pMin, pMax, pPosition));
	}
	SliderI * UI::GetSliderI(std::string pWindowKey, std::string pID)
	{
		return dynamic_cast<SliderI*>(m_Windows[pWindowKey].GetElement(pID));
	}
//================================Text=========================================

	void UI::CreateText(std::string pKey, std::string pID, std::string pText, ImVec2 pPosition)
	{
		m_Windows[pKey].NewElement(new Text(pID, pText, pPosition));

	}
	Text * UI::GetText(std::string pKey, std::string pID)
	{
		return dynamic_cast<Text*>(m_Windows[pKey].GetElement(pID));
	}
//===================================CheckBox================================

	void UI::CreateCheckbox(std::string pKey, std::string pID, bool pDefState, ImVec2 pPosition)
	{
		m_Windows[pKey].NewElement(new Checkbox(pID, pPosition, pDefState));
	}
	Checkbox * UI::GetCheckbox(std::string pWindowKey, std::string pID)
	{
		return dynamic_cast<Checkbox*>(m_Windows[pWindowKey].GetElement(pID));
	}


	UIWindow& UI::GetWindow(std::string pKey)
	{
		return m_Windows[pKey];
	}

};