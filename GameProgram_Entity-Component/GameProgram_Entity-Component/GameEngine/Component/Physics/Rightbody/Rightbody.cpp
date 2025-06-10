#include "Rightbody.h"

Rightbody::Rightbody(std::shared_ptr<Transform> _transform, bool _useGravity)
	: m_transform(_transform)
	, m_direction{ 0.0f, 0.0f, 0.0f }
	, m_velocity { 0.0f, 0.0f, 0.0f }
	, m_speed	 ( 0.0f )
	, m_gravity(0.8f) // 重力の強さ
	, m_useGravity(_useGravity) // 重力を有効にするかどうか
{
}

void Rightbody::Update()
{
    // 重力が有効な場合のみ加算
    if (m_useGravity) {
        m_velocity.y += m_gravity;
    }
    // 位置更新
    if (m_transform) {
        Vector3 pos = m_transform->GetPosition();
        pos.x += m_velocity.x;
        pos.y += m_velocity.y;
        pos.z += m_velocity.z;
        m_transform->SetPosition(pos);
    }

}
