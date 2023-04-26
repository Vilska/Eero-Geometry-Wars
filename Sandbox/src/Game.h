#pragma on

#include "Eero.h"

namespace Eero {

	class Game : public Layer
	{
	public:
		Game();

		virtual void OnAttach() override;

		virtual void OnUpdate(float deltaTime) override;
	private:
		void Restart();
		void AddScore();

		void SpawnPlayer();
		void SpawnEnemy();
		void SpawnBullet();

		void DestroyEnemyEffect(std::shared_ptr<Entity>& enemey);
		void RotateEntities(float deltaTime);

		void UserInput();
		void Collisions();
	private:
		std::shared_ptr<EntityManager> m_Entities;
		std::shared_ptr<Input> m_Input;
		std::shared_ptr<Collision> m_Collision;

		std::shared_ptr<Entity> m_Player;
		std::shared_ptr<Entity> m_ScoreText;

		bool m_Paused = false;
		int m_Score = 0;
		int m_EnemySpawnTimer = 0;
	};

}
