#pragma once
#include "../../Base/Component.h"


class Transform : public Component
{
private:
	Vector3 m_position;

public:
	Transform();

	// Component�̏������z�֐����I�[�o�[���C�h
	void Init() override {}
	void Update() override {}
	void Draw() override {}
	void Final() override {}

	void SetPosition(const Vector3& _position) { m_position = _position; }
	Vector3 GetPosition() const { return m_position; }

};

