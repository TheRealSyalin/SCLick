#pragma once

#include "../EventSystem/EventSystem.h"
#include "../y_Utility/Utility.h"


namespace SClick::Core::Renderer::Control
{
	class Control
	{
	public:
		Utility::Rect m_rect;
		Control* m_parent;

	public:
		Control(
			Control*													p_parent,
			Utility::Rect												p_rect, 
			Utility::Color												p_color,
			SClick::Core::EventSystem::EventManager&					p_eventManager);

		Control(
			Utility::Rect												p_rect,
			Utility::Color												p_color,
			SClick::Core::EventSystem::EventManager&					p_eventManager);

		~Control();

	public:
		bool OnClick(unsigned char mouseButton, bool passthrough);
		bool OnHover();

	private:
		SClick::Core::EventSystem::EventManager& m_eventManager;

	private:
		bool BoundsCheck(Utility::Vector2 mousePos);
	};
}
