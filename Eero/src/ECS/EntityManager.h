#pragma once

#include "Entity.h"

namespace Eero {

	class EntityManager
	{
	public:
		void Update();

		std::shared_ptr<Entity> PushEntity(const std::string& tag);

		std::vector<std::shared_ptr<Entity>>& GetEntities() { return m_Entities; }
		std::vector<std::shared_ptr<Entity>>& GetEntities(const std::string& tag) { return m_EntityMap[tag]; }
	private:
		void RemoveDeadEntities(std::vector<std::shared_ptr<Entity>>& eVec);
	private:
		std::vector<std::shared_ptr<Entity>> m_Entities;
		std::vector<std::shared_ptr<Entity>> m_EntitiesToAdd;
		std::map<std::string, std::vector<std::shared_ptr<Entity>>> m_EntityMap;

		size_t m_TotalEntities = 0;
	};

}
