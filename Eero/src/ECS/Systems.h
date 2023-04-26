#pragma once

#include "SFML/Graphics.hpp"

#include "Entity.h"
#include "EntityManager.h"

#include <functional>

namespace Eero {

	typedef std::tuple<std::shared_ptr<Entity>, std::shared_ptr<Entity>> EntityPairs;

	// Collision (it has to be on its own because of the Check functions)
	struct CollisionData
	{
		std::shared_ptr<Entity> EntityX;
		std::shared_ptr<Entity> EntityY;
	};

	class Collision
	{
		friend class Systems;
	public:
		void Listen(std::vector<std::shared_ptr<Entity>>& entities);

		void CheckCollision(const std::string& tagX, const std::string& tagY, const std::function<void(EntityPairs)>& func);
	private:
		Collision() = default;
	private:
		std::vector<std::shared_ptr<CollisionData>> m_Collisions;
		std::vector<std::shared_ptr<Entity>> m_Entities;
	};

	// Systems
	struct SystemsProps
	{
		std::shared_ptr<sf::RenderWindow>& RenderWindow;
		std::shared_ptr<EntityManager>& EntityManager;
	};

	class Systems
	{
	public:
		Systems() = default;
		Systems(const SystemsProps& props);

		void Run(float deltaTime);
		
		std::shared_ptr<Collision>& GetCollision() { return m_Collision; }
	private:
		void Movement(float deltaTime);
		void Render();
		void Lifespan();
	private:
		std::shared_ptr<sf::RenderWindow> m_RenderWindow;
		std::shared_ptr<EntityManager> m_EntityManager;
		std::vector<std::shared_ptr<Entity>> m_Entities;

		std::shared_ptr<Collision> m_Collision;
	};

}
