#include "TestObject.h"

TestObject::TestObject()
{
	AddComponent<Transform>();
	m_transform = GetComponent<Transform>();

	AddComponent<Rightbody>(m_transform, false);
	m_rightbody = GetComponent<Rightbody>();

	AddComponent<Collision>(m_transform, CollisionType::AABB);
	m_collision = GetComponent<Collision>();
}

void TestObject::Init()
{
	Entity::InitComponent();
	m_transform->SetPosition(VecGet(0.0f, 0.0f, 0.0f));
	m_collision->SetAABBData(64.0f, 64.0f);
	
}

void TestObject::Update()
{
	Entity::UpdateComponent();
}

void TestObject::Draw()
{
	Entity::DrawComponent();
}

void TestObject::Final()
{
	Entity::FinalComponent();
}
