#include "UIWindow.h"



namespace Simulator
{


	UIWindow::UIWindow(const std::string& pTitle, ImVec2 pSize, ImVec2 pPosition)
		: m_Title(pTitle), m_Size(pSize), m_Position(pPosition)
	{
		if (pPosition.x != 0.0f && pPosition.y != 0.0f)
		{
			m_LockedPosition = true;
		}

		if (pSize.x != 0.0f && pSize.y != 0.0f)
		{
			m_LockedSize = true;
		}
	}

	UIWindow::~UIWindow()
	{

	}

	//Drawing the window and its elements is acomplished by calling this function
	void UIWindow::Render()
	{
		if (m_LockedSize)
			ImGui::SetNextWindowSize(m_Size);
		if (m_LockedPosition)
			ImGui::SetNextWindowPos(m_Position);


		ImGui::Begin(m_Title.c_str(), NULL, GetWindowFlags());
			//Render Elements Here:

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