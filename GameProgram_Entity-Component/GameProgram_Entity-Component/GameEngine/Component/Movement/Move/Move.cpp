#include "Move.h"

Move::Move(std::shared_ptr<Transform> _transform, std::shared_ptr<Rightbody> _rightbody)
	: m_transform(_transform)
	, m_rightbody(_rightbody)
{

}

void Move::Update()
{
	m_rightbody->SetDirection(VecGet(0.0f, 0.0f, 0.0f));
	auto dir = m_rightbody->GetDirection();

	//if (CheckHitKey(KEY_INPUT_UP))    dir.y -= 1.0f; // 上はyマイナス
	//if (CheckHitKey(KEY_INPUT_DOWN))  dir.y += 1.0f; // 下はyプラス
	if (CheckHitKey(KEY_INPUT_LEFT))  dir.x -= 1.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT)) dir.x += 1.0f;

	if (VecSize(dir) > 0.0f) {
		dir = VecNorm(dir);
	}

	m_rightbody->SetDirection(dir);

	m_rightbody->SetVelocity(VecScale(dir, m_rightbody->GetSpeed()));
	Vector3 newPosition = VecAdd(m_transform->GetPosition(), m_rightbody->GetVelocity());
	m_transform->SetPosition(newPosition);
}

void Move::Draw()
{
#ifdef _DEBUG
	Vector3 pos = m_transform->GetPosition();
	Vector3 dir = m_rightbody->GetDirection();
	float arrowLength = 50.0f;

	if (dir.x != 0.0f || dir.y != 0.0f) {
		Vector3 end = {
			pos.x + dir.x * arrowLength,
			pos.y + dir.y * arrowLength,
			pos.z
		};
		DrawLine((int)pos.x, (int)pos.y, (int)end.x, (int)end.y, 0xffff00);
	}
#endif
}
