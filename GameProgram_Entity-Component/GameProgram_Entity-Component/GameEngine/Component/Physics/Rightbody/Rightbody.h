#pragma once
#include "../../Base/Component.h"
#include "../Transform/Transform.h"

class Rightbody : public Component
{
private:
	Vector3 m_direction;
	Vector3 m_velocity;
	float m_speed;


	std::shared_ptr<Transform> m_transform;
	float m_gravity = 0.8f; // 重力の強さ
	bool m_useGravity = true; // 重力を有効にするかどうか


public:
	Rightbody(std::shared_ptr<Transform> _transform, bool _useGravity);

	// Componentの純粋仮想関数をオーバーライド
	void Init() override {}
	void Update() override;
	void Draw() override {}
	void Final() override {}

	void SetDirection(const Vector3& _direction) { m_direction = _direction; }
	Vector3 GetDirection() const { return m_direction; }

	void SetVelocity(const Vector3& _velocity) { m_velocity = _velocity; }
	Vector3 GetVelocity() const { return m_velocity; }

	void SetSpeed(const float& _speed) { m_speed = _speed; }
	float GetSpeed() const { return m_speed; }

	void SetUseGravity(const bool& _enable) { m_useGravity = _enable; }
	bool IsUseEnabled() const { return m_useGravity; }

	float GetGravity() const { return m_gravity; }
	//void SetGravity(float _gravity) { m_gravity = _gravity; }

};

