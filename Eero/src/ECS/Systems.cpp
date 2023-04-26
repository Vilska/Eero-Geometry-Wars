#include "Systems.h"

#include "Core/Time.h"

namespace Eero {

	// Collision
	void Collision::Listen(std::vector<std::shared_ptr<Entity>>& entities)
	{
		for (auto& entityX : entities)
		{
			for (auto& entityY : entities)
			{
				if (entityX != entityY)
				{
					if ((entityX->cShape != nullptr && entityX->cTransform != nullptr && entityX->cCollision != nullptr) && (entityY->cShape != nullptr && entityY->cTransform != nullptr && entityY->cCollision != nullptr))
					{
						Vec2 entityXPos = entityX->cTransform->Pos;
						Vec2 entityYPos = entityY->cTransform->Pos;

						float entityXCollisionRadius = entityX->cCollision->Radius;
						float entityYCollisionRadius = entityY->cCollision->Radius;

						if ((entityXCollisionRadius + entityYCollisionRadius) > entityXPos.dist(entityYPos))
						{
							auto& collisionHandledX = entityX->cCollision->Handled;
							auto& collisionHandledY = entityY->cCollision->Handled;

							if (!(collisionHandledX == true && collisionHandledY == true))
							{
								auto collision = std::make_shared<CollisionData>(entityX, entityY);
								m_Collisions.push_back(collision);

								collisionHandledX = true;
								collisionHandledY = true;
							}
						}
					}
				}
			}
		}
	}

	void Collision::CheckCollision(const std::string& tagX, const std::string& tagY, const std::function<void(EntityPairs)>& func)
	{
		for (auto& collision : m_Collisions)
		{
			auto& entityXTag = collision->EntityX->GetTag();
			auto& entityYTag = collision->EntityY->GetTag();

			if (entityXTag == tagX && entityYTag == tagY)
			{
				func({ collision->EntityX, collision->EntityY });
				std::erase(m_Collisions, collision);
			}
			else if (entityXTag == tagY && entityYTag == tagX)
			{
				func({ collision->EntityY, collision->EntityX });
				std::erase(m_Collisions, collision);
			}
		}
	}
	
	// Systems
	Systems::Systems(const SystemsProps& props)
		: m_RenderWindow(props.RenderWindow), m_EntityManager(props.EntityManager)
	{
		m_Collision = std::shared_ptr<Collision>(new Collision);
	}

	void Systems::Run(float deltaTime)
	{
		m_Entities = m_EntityManager->GetEntities();

		Render();
		Movement(deltaTime);
		Lifespan();

		m_Collision->Listen(m_Entities);
	}

	void Systems::Movement(float deltaTime)
	{
		for (auto& entity : m_Entities)
		{
			if (entity->cShape != nullptr && entity->cTransform != nullptr)
			{
				float& posX = entity->cTransform->Pos.x;
				float& posY = entity->cTransform->Pos.y;
				float& velX = entity->cTransform->Velocity.x;
				float& velY = entity->cTransform->Velocity.y;

				float radius = entity->cShape->Circle.getRadius();
				if ((m_RenderWindow->getSize().x - posX) <= radius || (0 + posX) <= radius)
				{
					velX *= -1.0f;
				}
				else if ((m_RenderWindow->getSize().y - posY) <= radius || (0 + posY) <= radius)
				{
					velY *= -1.0f;
				}

				posX += (velX * deltaTime);
				posY += (velY * deltaTime);
			}
		}
	}

	void Systems::Render()
	{
		for (auto& entity : m_Entities) 
		{
			if (entity->cShape != nullptr && entity->cTransform != nullptr)
			{
				entity->cShape->Circle.setPosition(entity->cTransform->Pos.x, entity->cTransform->Pos.y);
				entity->cShape->Circle.setRotation(entity->cTransform->Angle);

				m_RenderWindow->draw(entity->cShape->Circle);
			}

			if (entity->cText != nullptr)
			{
				m_RenderWindow->draw(entity->cText->Text);
			}
		}
	}

	void Systems::Lifespan()
	{
		for (auto& entity : m_Entities)
		{
			if (entity->cShape != nullptr && entity->cLifespan != nullptr)
			{
				int& totalTime = entity->cLifespan->TotalTime;
				int actionTime = entity->cLifespan->ActionTime;

				if (totalTime > 0 && totalTime <= actionTime)
				{
					switch (entity->cLifespan->Effect)
					{
						case LifespanComponent::EffectTypes::Disappear:
						{
							break;
						}

						case LifespanComponent::EffectTypes::Fade:
						{
							// FillColor
							auto& fillColor = entity->cShape->Circle.getFillColor();
							int fillAlpha = fillColor.a - (fillColor.a / totalTime);

							// OutlineColor
							auto& outlineColor = entity->cShape->Circle.getOutlineColor();
							int outlineAlpha = outlineColor.a - (outlineColor.a / totalTime);

							entity->cShape->Circle.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, fillAlpha));
							entity->cShape->Circle.setOutlineColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, outlineAlpha));

							break;
						}

						case LifespanComponent::EffectTypes::Blink:
						{
							int halfTime = Time::Seconds(1) / 2;
							int modulo = actionTime % halfTime;

							// FillColor
							auto& fillColor = entity->cShape->Circle.getFillColor();
							static int originalFillAlpha = fillColor.a;
							int fillAlpha = fillColor.a;

							// OutlineColor
							auto& outlineColor = entity->cShape->Circle.getOutlineColor();
							static int originalOutlineAlpha = outlineColor.a;
							int outlineAlpha = outlineColor.a;

							// Adjustable with seconds, on every second entity fades out and fades in
							static int timer = Time::Seconds(1);

							if (timer > halfTime && timer <= timer)
							{
								fillAlpha = (originalFillAlpha * (timer - halfTime) / halfTime);
								outlineAlpha = (originalOutlineAlpha * (timer - halfTime) / halfTime);
							}
							else if (timer > 0 && timer <= halfTime)
							{
								fillAlpha += originalFillAlpha / halfTime;
								outlineAlpha += originalOutlineAlpha / halfTime;
							}
							else
							{
								timer = Time::Seconds(1);
							}
							timer--;

							entity->cShape->Circle.setFillColor(sf::Color(fillColor.r, fillColor.g, fillColor.b, fillAlpha));
							entity->cShape->Circle.setOutlineColor(sf::Color(outlineColor.r, outlineColor.g, outlineColor.b, outlineAlpha));

							break;
						}

						default:
							break;
					}
				}

				if (totalTime == 0)
				{
					entity->Destroy();
				}

				totalTime--;
			}
		}
	}

}
