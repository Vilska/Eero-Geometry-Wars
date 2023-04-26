#pragma once

#include "EventHandler.h"

namespace Eero {

	class Input
	{
	public:
		bool KeyPressed(const sf::Keyboard::Key& key);
		bool KeyReleased(const sf::Keyboard::Key& key);
		bool MouseButtonPressed(const sf::Mouse::Button& button);
		std::tuple<float, float> GetMousePosition();

		void SetEventList(std::map<std::string, std::vector<std::shared_ptr<Event>>> events) { m_Events = events; }
	private:
		std::map<std::string, std::vector<std::shared_ptr<Event>>> m_Events;
		float m_MousePosX, m_MousePosY = 0.0f;
	};

}
