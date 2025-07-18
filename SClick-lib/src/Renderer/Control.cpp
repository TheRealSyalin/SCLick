#include "pch.h"
#include "Control.h"

namespace SClick::Core::Renderer::Control
{
	Control::Control(
		Control*													p_parent,
		Utility::Rect												p_rect,
		Utility::Color												p_color,
		SClick::Core::EventSystem::EventManager&					p_eventManager)

		: m_rect(p_rect), m_parent(p_parent), m_eventManager(p_eventManager)
	{
		
	}

	Control::Control(
		Utility::Rect												p_rect,
		Utility::Color												p_color,
		SClick::Core::EventSystem::EventManager& p_eventManager)

		: m_rect(p_rect), m_parent(nullptr), m_eventManager(p_eventManager)
	{

	}

	Control::~Control()
	{}

	bool Control::OnClick(unsigned char mouseButton, bool passthrough)
	{
		Utility::Vector2 mousePos = m_eventManager.GetMouseButton(mouseButton);

		if (BoundsCheck(mousePos))
		{
			std::cout << "Clicked:" << mouseButton << ": " << mousePos.x << ", " << mousePos.y << std::endl;
			return true;
		}
		return false;
	}

	bool Control::OnHover()
	{
		if(m_eventManager.PassthroughEvent(EventType::MouseMove, [this](unsigned short _1, unsigned short _2) {

			if (BoundsCheck(Utility::Vector2(_1, _2)))
				std::cout << "Hover" << ": " << _1 << ", " << _2 << std::endl;

			return true;
			})) return true;

		return false;
	}
	bool Control::BoundsCheck(Utility::Vector2 mousePos)
	{
			Utility::Rect offsetPos{ m_rect.xPos, m_rect.yPos , m_rect.width, m_rect.height };

			if (m_parent)
				offsetPos = { m_rect.xPos + m_parent->m_rect.xPos, m_rect.yPos + m_parent->m_rect.yPos, m_rect.width, m_rect.height };

			if (mousePos.x > offsetPos.left && mousePos.x < offsetPos.right && mousePos.y > offsetPos.top && mousePos.y < offsetPos.bottom)
				return true;

			return false;
	}
}