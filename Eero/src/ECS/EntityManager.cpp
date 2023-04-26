#include "EntityManager.h"

#include <iostream>

namespace Eero {

	void EntityManager::Update()
	{
		for (auto& entity : m_EntitiesToAdd)
		{
			m_Entities.push_back(entity);
			m_EntityMap[entity->GetTag()].push_back(entity);
		}

		m_EntitiesToAdd.clear();

		RemoveDeadEntities(m_Entities);

		for (auto& [tag, entityVec] : m_EntityMap)
		{
			RemoveDeadEntities(entityVec);
		}
	}

	std::shared_ptr<Entity> EntityManager::PushEntity(const std::string& tag)
	{
		auto entity = std::shared_ptr<Entity>(new Entity(m_TotalEntities++, tag));

		m_EntitiesToAdd.push_back(entity);

		return entity;
	}

	void EntityManager::RemoveDeadEntities(std::vector<std::shared_ptr<Entity>>& eVec)
	{
		for (auto& entity : eVec)
		{
			std::erase_if(eVec, [](auto entity)
			{
				return !entity->IsActive();
			});
		}
	}
}