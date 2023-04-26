#pragma once

#include <vector>
#include <string>
#include <map>

#include "Event.h"

namespace Eero {

	class EventHandler
	{
	public:
		EventHandler(const std::shared_ptr<sf::RenderWindow>& window);

		void Listen();
		void Clear();

		std::map<std::string, std::vector<std::shared_ptr<Event>>>& GetEvents() { return m_Events; }
	private:
		std::shared_ptr<sf::RenderWindow> m_Window;
		std::map<std::string, std::vector<std::shared_ptr<Event>>> m_Events;
	};

}
