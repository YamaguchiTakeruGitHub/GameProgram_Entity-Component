#include "Jump.h"

Jump::Jump(std::shared_ptr<Transform> transform, std::shared_ptr<Rightbody> rightbody, std::shared_ptr<Collision> collision, float _jumpPower)
	: m_transform(transform)
	, m_rightbody(rightbody)
	, m_collision(collision)
	, m_isJumping(false) // ������Ԃł̓W�����v���Ă��Ȃ�
	, m_jumpPower(_jumpPower) // �W�����v�͂�ݒ�
{ 
}

void Jump::Init()
{
    m_isJumping = false;
}

void Jump::Update()
{
    // �n�ʂɂ��邩����
    if (m_collision && m_collision->GetIsGround()) {
        m_isJumping = false;
    }

    // �W�����v���́i�X�y�[�X�L�[���������u�ԁj
    if (!m_isJumping && m_collision && m_collision->GetIsGround()) {
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            if (m_rightbody) {
                Vector3 velocity = m_rightbody->GetVelocity();
                velocity.y = -m_jumpPower; // ������ɃW�����v
                m_rightbody->SetVelocity(velocity);
                m_isJumping = true;
            }
        }
    }
}
