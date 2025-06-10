#pragma once
#include "../../Base/Component.h"
#include "../../Physics/Transform/Transform.h"
#include "../../Physics/Rightbody/Rightbody.h"
#include "../../Physics/Colision/Colision.h"

class Jump : public Component
{
private:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Rightbody> m_rightbody;
	std::shared_ptr<Collision> m_collision;
	bool m_isJumping;  // ƒWƒƒƒ“ƒv’†‚©‚Ç‚¤‚©
	float m_jumpPower;
public:
	Jump(std::shared_ptr<Transform> transform, std::shared_ptr<Rightbody> rightbody, std::shared_ptr<Collision> collision, float _jumpPower = 15.0f);
	
	void Init() override;
	void Update() override;
	void Draw() override {};
	void Final() override {};

	void SetJumpPower(float power) { m_jumpPower = power; }
	float GetJumpPower() const { return m_jumpPower; }


};

