#include "Window.h"

namespace Eero {

	Window::Window(const std::string& title, float width, float height)
		: m_Width(width), m_Height(height) 
	{
		Init(title, width, height);
	}

	Window::~Window()
	{
		Shutdown();
	}


	void Window::Init(const std::string& title, float width, float height)
	{
		m_Window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title);
		m_Window->setVerticalSyncEnabled(true);
	}

	void Window::Shutdown()
	{
		m_Window->close();
	}

	void Window::Clear()
	{
		m_Window->clear(sf::Color::Black);
	}

	void Window::Display()
	{
		m_Window->display();
	}

	void Window::SetSize(float width, float height)
	{
		m_Width = width;
		m_Height = height;
	}

}