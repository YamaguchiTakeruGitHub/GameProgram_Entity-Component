#include "Jump.h"

Jump::Jump(std::shared_ptr<Transform> transform, std::shared_ptr<Rightbody> rightbody, std::shared_ptr<Collision> collision, float _jumpPower)
	: m_transform(transform)
	, m_rightbody(rightbody)
	, m_collision(collision)
	, m_isJumping(false) // 初期状態ではジャンプしていない
	, m_jumpPower(_jumpPower) // ジャンプ力を設定
{ 
}

void Jump::Init()
{
    m_isJumping = false;
}

void Jump::Update()
{
    // 地面にいるか判定
    if (m_collision && m_collision->GetIsGround()) {
        m_isJumping = false;
    }

    // ジャンプ入力（スペースキーを押した瞬間）
    if (!m_isJumping && m_collision && m_collision->GetIsGround()) {
        if (CheckHitKey(KEY_INPUT_SPACE)) {
            if (m_rightbody) {
                Vector3 velocity = m_rightbody->GetVelocity();
                velocity.y = -m_jumpPower; // 上方向にジャンプ
                m_rightbody->SetVelocity(velocity);
                m_isJumping = true;
            }
        }
    }
}
