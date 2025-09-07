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

		io.IniFilename = NULL;

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

	int UI::LoadUI(std::string pUIConfig)
	{
		//Check if We Already Loaded, if delete the old stuff and reload:

		if (m_Windows.size() != 0)
		{
			m_Windows.clear();
		}
		
		std::ifstream Source(pUIConfig, std::ios::in | std::ios::binary);

		if (!Source.is_open())
		{
			Log::GetSelf()->SetError("Unable to Open UI Config File");
			return 1;
		}
		//Json Parsing:

		Json Data = Json::parse(Source);
		Source.close();


		try
		{
			ImGui::GetStyle().WindowRounding = Data["Config"]["Rounding"];
			ImGui::GetStyle().FrameRounding = Data["Config"]["WidgetRounding"];
			ImGui::GetStyle().Alpha = Data["Config"]["Alpha"];
		}

		catch (...)
		{
			Log::GetSelf()->SetError("Invalid config");
		}

		for (auto& i : Data["Window"])
		{
			try
			{
				CreateWindowWidget(i["Title"], ImVec2(i["SizeX"], i["SizeY"]), ImVec2(i["PosX"], i["PosY"]), i["LockedPos"]);
			}
			catch (...)
			{
				Log::GetSelf()->SetError("Invalid Window Configuration");
				continue;
			}

			for (auto &j : i["Elements"])
			{
				try
				{
					/*
					
						I know it hurts to look at this......
						i probably should create a hash map and assign each type a function to be excuted.
						but for now this works, so just chill.
					*/
					std::string Type = j["Type"];
					if (Type == "Button")
					{
						CreateButton(i["Title"], j["ID"], ImVec2(j["PosX"], j["PosY"]), ImVec2(j["SizeX"], j["SizeY"]));
					}
					if (Type == "Text")
					{
						CreateText(i["Title"], j["ID"], j.value("Content", ""), ImVec2(j["PosX"], j["PosY"]));
					}
					if (Type == "SliderI")
					{
						CreateSliderI(i["Title"], j["ID"], j.value("Min", 0.0f), j.value("Max", 1.0f), ImVec2(j["PosX"], j["PosY"]));
					}
					if (Type == "SliderF")
					{
						CreateSliderF(i["Title"], j["ID"], j.value("Min", 0), j.value("Max", 10), ImVec2(j["PosX"], j["PosY"]));

					}
					if (Type == "Checkbox")
					{
						CreateCheckbox(i["Title"], j["ID"], j.value("State", false), ImVec2(j["PosX"], j["PosY"]));
					}
					if (Type == "InputF")
					{
						CreateInputF(i["Title"], j["ID"], j.value("Value", 0.0f), ImVec2(j["PosX"], j["PosY"]));
					}
					if (Type == "Input3F")
					{
						CreateInput3F(i["Title"], j["ID"], ImVec2(j["PosX"], j["PosY"]), j.value("Value1", 0.0f), j.value("Value2", 0.0f), j.value("Value3", 0.0f));
					}
				}
				catch (...)
				{
					Log::GetSelf()->SetInfo("Invalid Data Type");
					continue;
				}
			}
		}
		return 0;
	}


	void UI::Event()
	{
		/*
			TODO: fix this shit
		*/
		m_IsUsingKeyboard = ImGui::GetIO().WantCaptureKeyboard;
		m_IsUsingMouse = ImGui::GetIO().WantCaptureMouse;
	}

	void UI::Render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Rendering happens here
		//This Renders the windows and the windows render their elements
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

	int UI::CreateWindowWidget(std::string pKey, ImVec2 pSize, ImVec2 pPosition, bool LockedPos)
	{
		//we check if the window exists or not
		if (m_Windows.find(pKey) != m_Windows.end())
		{
			Log::GetSelf()->SetError("Window:%s already exists!", pKey);
			return 1;
		}

		m_Windows[pKey] = UIWindow(pKey, pSize, pPosition, LockedPos);
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
		if (pSize.x == 0)
		{
			pSize.x = pTitle.length()*8.0f + 20.0f;
			pSize.y = 20.0f;
		}

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
//=================================Input Float======================================
	void UI::CreateInputF(std::string pKey, std::string pID, float pDefValue, ImVec2 pPosition)
	{
		m_Windows[pKey].NewElement(new InputF(pID, pPosition, pDefValue));
	}

	InputF * UI::GetInputF(std::string pWindowKey, std::string pID)
	{
		return dynamic_cast<InputF*>(m_Windows[pWindowKey].GetElement(pID));

	}
//============================Input for 3 Floats===================================
	void UI::CreateInput3F(std::string pKey, std::string pID, ImVec2 pPosition, float pDefValue1, float pDefValue2, float pDefValue3)
	{
		m_Windows[pKey].NewElement(new Input3F(pID, pPosition, pDefValue1, pDefValue2, pDefValue3));

	}

	Input3F* UI::GetInput3F(std::string pWindowKey, std::string pID)
	{
		return dynamic_cast<Input3F*>(m_Windows[pWindowKey].GetElement(pID));

	}


	UIWindow& UI::GetWindow(std::string pKey)
	{
		return m_Windows[pKey];
	}

};