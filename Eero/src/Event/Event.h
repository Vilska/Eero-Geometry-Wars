#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

namespace Eero {

	struct KeyPressedEvent
	{
		sf::Keyboard::Key KeyCode;

		KeyPressedEvent(sf::Keyboard::Key& key)
			: KeyCode(key) {}
	};

	struct KeyReleasedEvent
	{
		sf::Keyboard::Key KeyCode;

		KeyReleasedEvent(sf::Keyboard::Key& key)
			: KeyCode(key) {}
	};

	struct MouseButtonPressedEvent
	{
		sf::Mouse::Button MouseButton;
		float MousePosX, MousePosY = 0.0f;

		MouseButtonPressedEvent(sf::Mouse::Button& button, float mouseX, float mouseY)
			: MouseButton(button), MousePosX(mouseX), MousePosY(mouseY) {}
	};

	struct MouseMovedEvent
	{
		float PosX, PosY = 0.0f;

		MouseMovedEvent(float x, float y)
			: PosX(x), PosY(y) {}
	};

	struct WindowEvent
	{
		std::string Type = "Default";
		float Width, Height = 0.0f;

		WindowEvent(std::string type)
			: Type(type) {}
		WindowEvent(std::string type, float x, float y)
			: Type(type), Width(x), Height(y) {}
	};

	class Event
	{
	public:
		std::shared_ptr<KeyPressedEvent> eKeyPressed;
		std::shared_ptr<KeyReleasedEvent> eKeyReleased;
		std::shared_ptr<MouseButtonPressedEvent> eMouseButton;
		std::shared_ptr<MouseMovedEvent> eMouseMoved;
		std::shared_ptr<WindowEvent> eWindow;
		bool m_Handled = false;
	};

}
