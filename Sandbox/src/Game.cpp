#include "Game.h"

namespace Eero {

	Game::Game()
	: m_Entities(Application::GetEntities()), m_Input(Application::GetInput()), m_Collision(Application::GetCollision()) {}

	void Game::OnAttach()
	{
		SpawnPlayer();
		SpawnEnemy();

		auto scoreText = m_Entities->PushEntity("scoreText");
		scoreText->cText = std::make_shared<TextComponent>("assets/Orbitron-Regular.ttf", "Score: 0", Vec2(30.0f, 30.0f), Vec3(255, 255, 255), 24);

		m_ScoreText = scoreText;
	}

	void Game::OnUpdate(float deltaTime)
	{
		UserInput();
		Collisions();
		RotateEntities(deltaTime);

		if (m_EnemySpawnTimer >= Time::Seconds(3)) // > in case of the frames wont match
		{
			if (m_Paused)
			{
				SpawnPlayer();
				m_Paused = false;
			}
			else
			{
				SpawnEnemy();
			}

			m_EnemySpawnTimer = 0;
		}

		m_EnemySpawnTimer++;
	}

	void Game::Restart()
	{
		m_Score = -100;
		AddScore();

		m_Paused = true;

		for (auto& entity : m_Entities->GetEntities())
		{
			if (entity->cTransform != nullptr)
				entity->cTransform->Velocity = { 0.0f, 0.0f };

			entity->cLifespan = std::make_shared<LifespanComponent>(Time::Seconds(0.5), Time::Seconds(0.5), LifespanComponent::EffectTypes::Fade);
		}

		m_EnemySpawnTimer = 0;
	}

	void Game::AddScore()
	{
		m_ScoreText->cText->SetText("Score: " + std::to_string(m_Score+= 100));
	}

	void Game::SpawnPlayer()
	{
		auto entity = m_Entities->PushEntity("player");

		entity->cShape = std::make_shared<ShapeComponent>(64.0f, 8, Vec3(10, 10, 10), Vec3(255, 0, 0), 4.0f);

		auto [x, y] = Application::GetWindow()->GetSize();
		entity->cTransform = std::make_shared<TransformComponent>(Vec2(x / 2, y / 2), Vec2(0.0f, 0.0f), 0.0f);
		
		entity->cCollision = std::make_shared<CollisionComponent>(64.0f);

		m_Player = entity;
	}

	void Game::SpawnEnemy()
	{
		auto entity = m_Entities->PushEntity("enemy");

		// Shape
		entity->cShape = std::make_shared<ShapeComponent>(64.0f, Random::Calculate(8, 3), Vec3(10, 10, 10), Vec3(Random::Calculate(255, 1), Random::Calculate(255, 1), Random::Calculate(255, 1)), 4.0f);

		// Position
		auto& window = Application::GetWindow();
		auto [x, y] = window->GetSize();
		float radius = entity->cShape->Circle.getRadius();

		float posX = Random::Calculate(x - radius, radius);
		float posY = Random::Calculate(y - radius, radius);

		entity->cTransform = std::make_shared<TransformComponent>(Vec2(posX, posY), Vec2(300.0f, 300.0f), 0.0f);

		// Collision
		entity->cCollision = std::make_shared<CollisionComponent>(64.0f);
	}

	void Game::SpawnBullet()
	{
		auto entity = m_Entities->PushEntity("bullet");

		// Shape
		entity->cShape = std::make_shared<ShapeComponent>(16.0f, 32, Vec3(255, 255, 255), Vec3(255, 0, 0), 4.0f);
		
		// Transform
		entity->cTransform = std::make_shared<TransformComponent>(Vec2(m_Player->cTransform->Pos.x, m_Player->cTransform->Pos.y), Vec2(0.0f, 0.0f), 0.0f);

		auto [mouseX, mouseY] = m_Input->GetMousePosition();
		float playerX = m_Player->cTransform->Pos.x;
		float playerY = m_Player->cTransform->Pos.y;

		Vec2 mousePos = { mouseX, mouseY };
		Vec2 playerPos = { playerX, playerY };

		Vec2 difference = mousePos - playerPos;
		Vec2 normal = { difference.x / difference.length(), difference.y / difference.length() };
		entity->cTransform->Velocity = { 600.0f * normal.x, 600.0f * normal.y };
 
		// Lifespan
		entity->cLifespan = std::make_shared<LifespanComponent>(Time::Seconds(0.8), Time::Seconds(0.5), LifespanComponent::EffectTypes::Fade);

		// Collision
		entity->cCollision = std::make_shared<CollisionComponent>(16.0f);
	}

	void Game::DestroyEnemyEffect(std::shared_ptr<Entity>& enemy)
	{
		auto& enemyShape = enemy->cShape;
		Vec3 enemyFillColor = enemyShape->GetFillColor();
		Vec3 enemyOutlineColor = enemyShape->GetOutlineColor();
		Vec2 enemyPos = enemy->cTransform->Pos;
		int points = enemyShape->GetPointCount();

		int angle = 360 / points;
		int actualAngle = 0;

		for (int i = 0; i < points; i++)
		{
			actualAngle += angle;
			Vec2 circlePoint = { enemyPos.x + (float)cos(actualAngle * (3.14159 / 180)), enemyPos.y + (float)sin(actualAngle * (3.14159 / 180)) };
			Vec2 difference = circlePoint - enemyPos;
			Vec2 normal = { difference.x / difference.length(), difference.y / difference.length() };

			auto effectEntity = m_Entities->PushEntity("effectEntity");
			effectEntity->cShape = std::make_shared<ShapeComponent>(16.0f, points, enemyFillColor, enemyOutlineColor, 4.0f);
			effectEntity->cTransform = std::make_shared<TransformComponent>(enemyPos, Vec2(300.0f * normal.x, 300.0f * normal.y), 0.0f);
			effectEntity->cLifespan = std::make_shared<LifespanComponent>(Time::Seconds(0.6), Time::Seconds(0.4), LifespanComponent::EffectTypes::Fade);
		}
	}

	void Game::RotateEntities(float deltaTime)
	{
		for (auto& entity : m_Entities->GetEntities())
		{
			if (entity->cTransform != nullptr)
				entity->cTransform->Angle += 100.0f * deltaTime;
		}
	}

	void Game::UserInput()
	{
		if (m_Input->KeyPressed(KEY_W))
			m_Player->cTransform->Velocity.y = -300.0f;
		if (m_Input->KeyPressed(KEY_S))
			m_Player->cTransform->Velocity.y = 300.0f;
		if (m_Input->KeyPressed(KEY_A))
			m_Player->cTransform->Velocity.x = -300.0f;
		if (m_Input->KeyPressed(KEY_D))
			m_Player->cTransform->Velocity.x = 300.0f;

		if (m_Input->KeyReleased(KEY_W))
			m_Player->cTransform->Velocity.y = 0.0f;
		if (m_Input->KeyReleased(KEY_S))
			m_Player->cTransform->Velocity.y = 0.0f;
		if (m_Input->KeyReleased(KEY_A))
			m_Player->cTransform->Velocity.x = 0.0f;
		if (m_Input->KeyReleased(KEY_D))
			m_Player->cTransform->Velocity.x = 0.0f;

		if (m_Input->MouseButtonPressed(MOUSE_1))
			SpawnBullet();
	}

	void Game::Collisions()
	{
		m_Collision->CheckCollision("enemy", "bullet", [&](EntityPairs entities)
		{
			auto& [entityX, entityY] = entities;

			entityX->cLifespan = std::make_shared<LifespanComponent>(Time::Seconds(0.15), Time::Seconds(0.15), LifespanComponent::EffectTypes::Fade);
			DestroyEnemyEffect(entityX);

			entityY->Destroy();

			AddScore();
		});

		m_Collision->CheckCollision("enemy", "player", [&](EntityPairs entities)
		{
			auto& [entityX, entityY] = entities;

			Restart();
		});
	}

	std::shared_ptr<Application> CreateApplication()
	{
		AppProps props = {"Geometry Wars", 1280.0f, 720.0f};
		std::shared_ptr<Application> app = std::make_shared<Application>(props);

		app->PushLayer<Game>();

		return app;
	}


}
