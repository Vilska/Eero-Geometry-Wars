#include "Application.h"
#include "ECS/Systems.h"

namespace Eero {

	std::shared_ptr<EntityManager> Application::s_Entities = nullptr;
	std::shared_ptr<Input> Application::s_Input = nullptr;
	std::shared_ptr<Window> Application::s_Window = nullptr;
	std::shared_ptr<Collision> Application::s_Collision = nullptr;

	Application::Application(const AppProps& props)
	{
		Init(props);
	}

	Application::~Application()
	{
		Shutdown();
	}

	void Application::Init(const AppProps& props)
	{
		m_Window = std::make_shared<Window>(props.WindowTitle, props.WindowWidth, props.WindowHeight);
		m_Events = std::make_shared<EventHandler>(m_Window->GetWindow());
		m_Entities = std::make_shared<EntityManager>();
		m_Input = std::make_shared<Input>();

		SystemsProps systemsProps = { m_Window->GetWindow(), m_Entities };
		m_Systems = std::make_shared<Systems>(systemsProps);

		s_Entities = m_Entities;
		s_Input = m_Input;
		s_Window = m_Window;
		s_Collision = m_Systems->GetCollision();
	}

	void Application::Shutdown()
	{
		for (auto& layer : m_Layers)
		{
			layer->OnDetach();
		}

		m_Window->Shutdown();
	}

	void Application::Run()
	{
		sf::Clock clock;

		while (m_Running)
		{
			auto time = clock.getElapsedTime().asSeconds();
			m_Timestep = Time::CalculateDeltaTime(time);

			m_Events->Listen();
			m_Input->SetEventList(m_Events->GetEvents());

			for (auto& layer : m_Layers)
			{
				layer->OnUpdate(m_Timestep);
			}

			m_Entities->Update();

			m_Window->Clear();
			m_Systems->Run(m_Timestep);
			m_Window->Display();

			CheckWindowEvents();

			m_Events->Clear();

		}
	}

	void Application::CheckWindowEvents()
	{
		for (auto& [tag, entityVec] : m_Events->GetEvents())
		{
			if (tag == "window")
			{
				for (auto& e : entityVec)
				{
					if (e->eWindow->Type == "closed")
					{
						m_Running = false;
					}
					else if (e->eWindow->Type == "resized" && !e->m_Handled)
					{
						m_Window->SetSize(e->eWindow->Width, e->eWindow->Height);
					}

					e->m_Handled = true;
				}
			}
		}
	}

}