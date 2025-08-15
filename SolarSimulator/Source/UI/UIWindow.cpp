#include "UIWindow.h"



namespace Simulator
{


	UIWindow::UIWindow(const std::string& pTitle, ImVec2 pSize, ImVec2 pPosition, bool pLockedPos)
		: m_Title(pTitle), m_Size(pSize), m_Position(pPosition), m_LockedPosition(pLockedPos)
	{


		if (pSize.x != 0.0f && pSize.y != 0.0f)
		{
			m_LockedSize = true;
		}
	}

	UIWindow::~UIWindow()
	{
		for (auto &i : m_Elements)
		{
			Log::GetSelf()->SetInfo("%s: Free Element: %s", m_Title, i.first);
			delete i.second; // Delete Elements from the heap
		}
	}

	//Drawing the window and its elements is acomplished by calling this function
	void UIWindow::Render()
	{
		if (m_LockedSize)
			ImGui::SetNextWindowSize(m_Size);
		if (m_LockedPosition)
			ImGui::SetNextWindowPos(m_Position);


		ImGui::Begin(m_Title.c_str());
			//Render Elements Here:

		for (auto &i : m_Elements)
		{
			if (!i.second->GetRenderState())
				continue;//Skip Rendering if it was disabled.

			i.second->Render();
		}

		ImGui::End();
	}

	void UIWindow::SetWindowSize(ImVec2 pSize)
	{
		if (pSize.x < 0.0f || pSize.y < 0.0f)
		{
			m_LockedSize = false;
			return;
		}
		m_LockedSize = true;
		m_Size = pSize;
	}

	void UIWindow::SetWindowPosition(ImVec2 pPosition)
	{
		if (pPosition.x < 0.0f || pPosition.y < 0.0f)
		{
			m_LockedPosition = false;
			return;
		}
		m_LockedPosition = true;
		m_Position = pPosition;
	}

	void UIWindow::SetWindowTitle(std::string pTitle)
	{
		if (pTitle.length() == 0)
			return;
		m_Title = pTitle;
	}


	void UIWindow::NewElement(Element* pElement)
	{
		m_Elements[pElement->GetID()] = pElement;
	}

	Element * UIWindow::GetElement(std::string pID)
	{
		if (m_Elements.find(pID) == m_Elements.end())
		{
			return NULL;
		}
		return m_Elements[pID];
	}

	ImGuiWindowFlags UIWindow::GetWindowFlags()
	{
		ImGuiWindowFlags Flags;

		if (m_Collapsable)
			Flags |= ImGuiWindowFlags_NoCollapse;
		if (m_NoScrollbar)
			Flags |= ImGuiWindowFlags_NoScrollbar;
		if (m_NoTitleBar)
			Flags |= ImGuiWindowFlags_NoTitleBar;
		return Flags;
	}



};