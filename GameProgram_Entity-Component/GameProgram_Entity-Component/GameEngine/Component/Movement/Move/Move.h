#pragma once
#include "../../Base/Component.h"
#include "../../Physics/Transform/Transform.h"
#include "../../Physics/Rightbody/Rightbody.h"

class Move : public Component
{
private:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Rightbody> m_rightbody;

public:
	Move(std::shared_ptr<Transform> _transform, std::shared_ptr<Rightbody> _rightbody);

	void Init() override {}
	void Update() override;
	void Draw() override;
	void Final() override {}


	void SetPosition(const Vector3& _position) { m_transform->SetPosition(_position); }
	Vector3 GetPosition() const { return m_transform->GetPosition(); }

};

