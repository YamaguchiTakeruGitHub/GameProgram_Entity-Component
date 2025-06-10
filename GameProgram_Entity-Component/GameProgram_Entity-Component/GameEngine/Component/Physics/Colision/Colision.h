#pragma once
#include "../../Base/Component.h"
#include "../Transform/Transform.h"
#include <variant>

struct CircleData
{
	float m_radius;
};

struct AABBData
{
	float halfWidth;
	float halfHeight;
};

enum class CollisionType
{
	Circle,
	AABB,
};

enum class Prioriy
{
	Static,
	Dynamic,
};

/// <summary>
/// ìñÇΩÇËîªíËÉNÉâÉXÅ@à¯êî(Transform, CollisionType)
/// </summary>
class Collision : public Component
{
private:
	std::shared_ptr<Transform> m_transform;

	std::variant<CircleData, AABBData> m_shapeData;

	std::weak_ptr<Collision> m_lastCollidedWith;

	CollisionType m_collisionType;
	Prioriy m_prioriy;

	bool m_isColliding;
	bool m_isGround;

public:
	Collision(std::shared_ptr<Transform> _transform, CollisionType _collisionType);

	void Init() override {};
	void Update() override {};
	void Draw() override;
	void Final() override {};

	void CheckCollision(const std::shared_ptr<Collision>& _other, bool _applyPushBack, Prioriy _priority);
	
	bool GetIsColliding() const { return m_isColliding; }

	bool GetIsGround() const { return m_isGround; }

	void SetCircleData(float _radius);
	CircleData GetCircleData() const;

	void SetAABBData(float _halfWidth, float _halfHeight);
	AABBData GetAABBData() const;

	std::shared_ptr<Collision> GetLastCollidedWith() { return m_lastCollidedWith.lock(); }

};

