#pragma once

#include <SFML/Graphics.hpp>

namespace Eero {

	class Window
	{
	public:
		Window(const std::string& title, float width, float height);
		~Window();

		void Clear();
		void Display();

		std::shared_ptr<sf::RenderWindow>& GetWindow() { return m_Window; } // actual sf::RenderWindow

		void Shutdown();

		void SetSize(float width, float height);
		std::tuple<float, float> GetSize() const { return { m_Width, m_Height }; }
	private:
		void Init(const std::string& title, float width, float height);
	private:
		std::shared_ptr<sf::RenderWindow> m_Window;
		float m_Width, m_Height = 0.0f;
	};

}
