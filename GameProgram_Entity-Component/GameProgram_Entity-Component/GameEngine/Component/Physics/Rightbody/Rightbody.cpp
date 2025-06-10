#include "Rightbody.h"

Rightbody::Rightbody(std::shared_ptr<Transform> _transform, bool _useGravity)
	: m_transform(_transform)
	, m_direction{ 0.0f, 0.0f, 0.0f }
	, m_velocity { 0.0f, 0.0f, 0.0f }
	, m_speed	 ( 0.0f )
	, m_gravity(0.8f) // �d�͂̋���
	, m_useGravity(_useGravity) // �d�͂�L���ɂ��邩�ǂ���
{
}

void Rightbody::Update()
{
    // �d�͂��L���ȏꍇ�̂݉��Z
    if (m_useGravity) {
        m_velocity.y += m_gravity;
    }
    // �ʒu�X�V
    if (m_transform) {
        Vector3 pos = m_transform->GetPosition();
        pos.x += m_velocity.x;
        pos.y += m_velocity.y;
        pos.z += m_velocity.z;
        m_transform->SetPosition(pos);
    }

}
