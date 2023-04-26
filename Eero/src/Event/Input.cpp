#include "Input.h"

namespace Eero {

	bool Input::KeyPressed(const sf::Keyboard::Key& key)
	{
		for (auto& [tag, eventVec] : m_Events)
		{
			if (tag == "keyPressed")
			{
				for (auto& e : eventVec)
				{
					if (e->eKeyPressed->KeyCode == key && !e->m_Handled)
					{
						e->m_Handled = true;
						return true;
					}
				}
			}
		}

		return false;
	}

	bool Input::KeyReleased(const sf::Keyboard::Key& key)
	{
		for (auto& [tag, eventVec] : m_Events)
		{
			if (tag == "keyReleased")
			{
				for (auto& e : eventVec)
				{
					if (e->eKeyReleased->KeyCode == key && !e->m_Handled)
					{
						e->m_Handled = true;
						return true;
					}
				}
			}
		}

		return false;
	}

	bool Input::MouseButtonPressed(const sf::Mouse::Button& button)
	{
		for (auto& [tag, eventVec] : m_Events)
		{
			if (tag == "mouseButton")
			{
				for (auto& e : eventVec)
				{
					if (e->eMouseButton->MouseButton == button && !e->m_Handled)
					{
						// Set the mouse position when it is only clicked
						m_MousePosX = e->eMouseButton->MousePosX;
						m_MousePosY = e->eMouseButton->MousePosY;

						e->m_Handled = true;
						return true;
					}
				}
			}
		}

		return false;
	}

	std::tuple<float, float> Input::GetMousePosition()
	{
		for (auto& [tag, eventVec] : m_Events)
		{
			if (tag == "mouseMoved")
			{
				for (auto& e : eventVec)
				{
					if (!e->m_Handled)
					{
						m_MousePosX = e->eMouseMoved->PosX;
						m_MousePosY = e->eMouseMoved->PosY;
						e->m_Handled = true;
					}
				}
			}
		}

		return { m_MousePosX, m_MousePosY };
	}

}