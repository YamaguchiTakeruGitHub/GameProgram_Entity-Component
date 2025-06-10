#include "Player.h"

Player::Player()
{
	AddComponent<Transform>();
	m_transform = GetComponent<Transform>();

	AddComponent<Rightbody>(m_transform, true);
	m_rightbody = GetComponent<Rightbody>();

	AddComponent<Collision>(m_transform, CollisionType::Circle);
	//AddComponent<Collision>(m_transform, CollisionType::AABB);
	m_collision = GetComponent<Collision>();

	AddComponent<Move>(m_transform, m_rightbody);
	m_move = GetComponent<Move>();

	AddComponent<Jump>(m_transform, m_rightbody, m_collision, 30.0f);
	m_jump = GetComponent<Jump>();
}

void Player::Init()
{
	Entity::InitComponent();
	m_collision->SetCircleData(20.0f); // ”¼Œa50‚Ì‰~Œ`“–‚½‚è”»’è‚ğİ’è
	m_transform->SetPosition(VecAdd(m_transform->GetPosition(), VecGet(100.0f, 350.0f, 0.0f))); // ‰ŠúˆÊ’u‚ğİ’è
	m_rightbody->SetSpeed(1.0f); // ˆÚ“®‘¬“x‚ğİ’è
}

void Player::Update()
{
	Entity::UpdateComponent();
}

void Player::Draw()
{
	Entity::DrawComponent();
}

void Player::Final()
{
	Entity::FinalComponent();
}
