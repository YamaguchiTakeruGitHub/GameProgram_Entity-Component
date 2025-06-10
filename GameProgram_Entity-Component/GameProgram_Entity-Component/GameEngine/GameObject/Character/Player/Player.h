#pragma once
#include "../Base/Character.h"

class Player : public Character
{
private:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Rightbody> m_rightbody;

	std::shared_ptr<Collision> m_collision;
	std::shared_ptr<Move> m_move;
	std::shared_ptr<Jump> m_jump;

public:
	Player();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	std::shared_ptr<Transform> GetTransform() const { return m_transform; }
	std::shared_ptr<Rightbody> GetRightbody() const { return m_rightbody; }
	std::shared_ptr<Collision> GetCollision() const { return m_collision; }
	std::shared_ptr<Move> GetMove() const { return m_move; }

};

