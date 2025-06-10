#pragma once
#include "../Base/GameObject.h"

class TestObject : public GameObject
{
private:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Rightbody> m_rightbody;
	std::shared_ptr<Collision> m_collision;

public:
	TestObject();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Final() override;

	std::shared_ptr<Transform> GetTransform() const { return m_transform; }
	std::shared_ptr<Rightbody> GetRightbody() const { return m_rightbody; }
	std::shared_ptr<Collision> GetCollision() const { return m_collision; }

};

