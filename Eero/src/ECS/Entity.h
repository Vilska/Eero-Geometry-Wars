#pragma once

#include "Components.h"

namespace Eero {

	class Entity
	{
		friend class EntityManager;
	public:
		std::shared_ptr<TransformComponent> cTransform;
		std::shared_ptr<ShapeComponent> cShape;
		std::shared_ptr<CollisionComponent> cCollision;
		std::shared_ptr<LifespanComponent> cLifespan;
		std::shared_ptr<TextComponent> cText;

		bool IsActive() const { return m_Active; }
		const std::string& GetTag() const { return m_Tag; }
		const size_t GetIdentifier() const { return m_ID; }
		void Destroy() { m_Active = false; }
	private:
		Entity(const size_t id, const std::string& tag) 
		: m_ID(id), m_Tag(tag) {}
	private:
		bool m_Active = true;
		size_t m_ID = 0;
		std::string m_Tag = "Default";
	};

}
