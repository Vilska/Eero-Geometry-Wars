#include "EventHandler.h"

namespace Eero {

	EventHandler::EventHandler(const std::shared_ptr<sf::RenderWindow>& window)
		: m_Window(window) 
	{
		Clear();
	}

	void EventHandler::Listen()
	{
		sf::Event sfEvent;

		while (m_Window->pollEvent(sfEvent))
		{
			switch (sfEvent.type)
			{
				case sf::Event::KeyPressed:
				{
					auto eventX = std::make_shared<Event>();
					eventX->eKeyPressed = std::make_shared<KeyPressedEvent>(sfEvent.key.code);

					m_Events["keyPressed"].push_back(eventX);

					break;
				}

				case sf::Event::KeyReleased:
				{
					auto eventX = std::make_shared<Event>();
					eventX->eKeyReleased = std::make_shared<KeyReleasedEvent>(sfEvent.key.code);

					m_Events["keyReleased"].push_back(eventX);

					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					auto eventX = std::make_shared<Event>();
					eventX->eMouseButton = std::make_shared<MouseButtonPressedEvent>(sfEvent.mouseButton.button, sfEvent.mouseButton.x, sfEvent.mouseButton.y);

					m_Events["mouseButton"].push_back(eventX);

					break;
				}

				case sf::Event::MouseMoved:
				{
					auto eventX = std::make_shared<Event>();
					eventX->eMouseMoved = std::make_shared<MouseMovedEvent>(sfEvent.mouseMove.x, sfEvent.mouseMove.y);

					m_Events["mouseMoved"].push_back(eventX);

					break;
				}

				case sf::Event::Closed:
				{
					auto eventX = std::make_shared<Event>();
					eventX->eWindow = std::make_shared<WindowEvent>("closed");

					m_Events["window"].push_back(eventX);

					break;
				}

				case sf::Event::Resized:
				{
					auto eventX = std::make_shared<Event>();
					eventX->eWindow = std::make_shared<WindowEvent>("resized", sfEvent.size.width, sfEvent.size.height);

					m_Events["window"].push_back(eventX);

					break;
				}


				default:
					break;
			}
		}
	}

	void EventHandler::Clear()
	{
		m_Events.clear();
	}

}