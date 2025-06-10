#define NOMINMAX        // ← これを追加
#include "Colision.h"
#include <algorithm>


namespace DebugData
{
	static constexpr int k_debugColor = 0xff0000;
}

Collision::Collision(std::shared_ptr<Transform> _transform, CollisionType _collisionType)
	: m_transform		(_transform)
	, m_collisionType	(_collisionType)
	, m_isColliding		(false)
	
{
	if (m_collisionType == CollisionType::Circle)
	{
		m_shapeData = CircleData{ 1.0f };
	}
	else if (m_collisionType == CollisionType::AABB)
	{
		m_shapeData = AABBData{ 1.0f, 1.0f };
	}

}

void Collision::Draw()
{
#ifdef _DEBUG
	if (m_collisionType == CollisionType::Circle) DrawCircle(m_transform->GetPosition().x, m_transform->GetPosition().y, GetCircleData().m_radius, DebugData::k_debugColor, false);
	else if (m_collisionType == CollisionType::AABB) {
		AABBData aabb = GetAABBData();
		Vector3 pos = m_transform->GetPosition();
		int left = (int)(pos.x - aabb.halfWidth);
		int right = (int)(pos.x + aabb.halfWidth);
		int top = (int)(pos.y - aabb.halfHeight);
		int bottom = (int)(pos.y + aabb.halfHeight);
		DrawBox(left, top, right, bottom, DebugData::k_debugColor, false);
	}
#endif // _DEBUG

}

void Collision::CheckCollision(const std::shared_ptr<Collision>& _other, bool _applyPushBack, Prioriy _priority)
{
	m_isGround = false;

	if (m_collisionType == CollisionType::Circle && _other->m_collisionType == CollisionType::Circle)
	{
		Vector3 posSub = VecSub(m_transform->GetPosition(), _other->m_transform->GetPosition());
		float posSize = VecSize(posSub);
		float radiusSum = GetCircleData().m_radius + _other->GetCircleData().m_radius;

		if (posSize <= radiusSum)
		{
			m_isColliding = true;

			m_lastCollidedWith = _other;

			if (_applyPushBack)
			{
				float pushBackDistance = radiusSum - posSize;
				Vector3 pushBackDirection = VecNorm(posSub);
				Vector3 pushbackVector = VecScale(pushBackDirection, pushBackDistance);

				if (_priority == Prioriy::Dynamic)
				{
					Vector3 newPosition = VecAdd(m_transform->GetPosition(), pushbackVector);
					m_transform->SetPosition(newPosition);
				}
				else if (_priority == Prioriy::Static)
				{
				}
			}
		}
		else
		{
			m_isColliding = false;
			m_lastCollidedWith.reset();
		}
	}//===<CircleOrCircle>(end)===
	else if (m_collisionType == CollisionType::AABB && _other->m_collisionType == CollisionType::AABB)
	{
		AABBData aabb1 = GetAABBData();
		AABBData aabb2 = _other->GetAABBData();
		Vector3 pos1 = m_transform->GetPosition();
		Vector3 pos2 = _other->m_transform->GetPosition();
		if (pos1.x - aabb1.halfWidth < pos2.x + aabb2.halfWidth &&
			pos1.x + aabb1.halfWidth > pos2.x - aabb2.halfWidth &&
			pos1.y - aabb1.halfHeight < pos2.y + aabb2.halfHeight &&
			pos1.y + aabb1.halfHeight > pos2.y - aabb2.halfHeight)
		{
			m_isColliding = true;
			m_lastCollidedWith = _other;
			if (_applyPushBack)
			{
				float pushBackX = 0.0f;
				float pushBackY = 0.0f;
				if (pos1.x < pos2.x) {
					pushBackX = (pos1.x + aabb1.halfWidth) - (pos2.x - aabb2.halfWidth);
				}
				else {
					pushBackX = (pos1.x - aabb1.halfWidth) - (pos2.x + aabb2.halfWidth);
				}
				if (pos1.y < pos2.y) {
					pushBackY = (pos1.y + aabb1.halfHeight) - (pos2.y - aabb2.halfHeight);
				}
				else {
					pushBackY = (pos1.y - aabb1.halfHeight) - (pos2.y + aabb2.halfHeight);
				}
				Vector3 pushbackVector{ pushBackX, pushBackY, 0.0f };
				if (_priority == Prioriy::Dynamic)
				{
					Vector3 newPosition = VecAdd(m_transform->GetPosition(), pushbackVector);
					m_transform->SetPosition(newPosition);
				}
				else if (_priority == Prioriy::Static)
				{
				}
			}
		}
		else
		{
			m_isColliding = false;
			m_lastCollidedWith.reset();
		}
	}//===<AABBOrAABB>(end)===
	else if ((m_collisionType == CollisionType::AABB && _other->m_collisionType == CollisionType::Circle) ||(m_collisionType == CollisionType::Circle && _other->m_collisionType == CollisionType::AABB))
	{
		// AABBをaabbCol, 円をcircleColに揃える
		Collision* aabbCol = (m_collisionType == CollisionType::AABB) ? this : _other.get();
		Collision* circleCol = (m_collisionType == CollisionType::Circle) ? this : _other.get();
		Vector3 aabbPos = aabbCol->m_transform->GetPosition();
		AABBData aabb = aabbCol->GetAABBData();
		Vector3 circlePos = circleCol->m_transform->GetPosition();
		float radius = circleCol->GetCircleData().m_radius;

		// 最近傍点
		float closestX = std::max(aabbPos.x - aabb.halfWidth, std::min(circlePos.x, aabbPos.x + aabb.halfWidth));
		float closestY = std::max(aabbPos.y - aabb.halfHeight, std::min(circlePos.y, aabbPos.y + aabb.halfHeight));
		float dx = circlePos.x - closestX;
		float dy = circlePos.y - closestY;
		float distSq = dx * dx + dy * dy;

		if (distSq <= (radius * radius))
		{
			m_isColliding = true;
			m_lastCollidedWith = _other;

			if (_applyPushBack)
			{
				float dist = std::sqrt(distSq);
				float overlap = radius - dist;
				if (overlap > 0.0f)
				{
					// 押し戻しベクトル（最近傍点→円中心方向）
					Vector3 pushDir = { dx, dy, 0.0f };
					if (dist != 0.0f) {
						pushDir = VecNorm(pushDir);
					}
					else {
						// 完全に重なっている場合は適当な方向
						pushDir = { 1.0f, 0.0f, 0.0f };
					}
					Vector3 pushbackVector = VecScale(pushDir, overlap);


					// --- ここから地面判定追加 ---
					// Y方向の押し戻しが下向き（負）かつ、X方向よりY方向の押し戻しが大きい場合
					if (pushbackVector.y < 0.0f && std::abs(pushbackVector.y) > std::abs(pushbackVector.x)) {
						m_isGround = true;
					}
					// --- ここまで ---

					// Dynamic/Staticの優先度でどちらを動かすか
					if (m_collisionType == CollisionType::Circle && _priority == Prioriy::Dynamic)
					{
						// 円側を動かす
						Vector3 newPos = VecAdd(circleCol->m_transform->GetPosition(), pushbackVector);
						circleCol->m_transform->SetPosition(newPos);
					}
					else if (m_collisionType == CollisionType::AABB && _priority == Prioriy::Dynamic)
					{
						// AABB側を動かす（通常は円側を動かすことが多い）
						Vector3 newPos = VecSub(aabbCol->m_transform->GetPosition(), pushbackVector);
						aabbCol->m_transform->SetPosition(newPos);
					}
					// Staticの場合は何もしない
				}
			}
		}
		else
		{
			m_isColliding = false;
			m_lastCollidedWith.reset();
		}
	}
}

void Collision::SetCircleData(float _radius)
{
	if (m_collisionType == CollisionType::Circle)
	{
		std::get<CircleData>(m_shapeData).m_radius = _radius;
	}
}

CircleData Collision::GetCircleData() const
{
	if (m_collisionType == CollisionType::Circle)
	{
		return std::get<CircleData>(m_shapeData);
	}

	return CircleData{ 0.0f };
}

void Collision::SetAABBData(float _halfWidth, float _halfHeight)
{
	if (m_collisionType == CollisionType::AABB)
	{
		std::get<AABBData>(m_shapeData).halfWidth = _halfWidth;
		std::get<AABBData>(m_shapeData).halfHeight = _halfHeight;
	}
}

AABBData Collision::GetAABBData() const
{
	if (m_collisionType == CollisionType::AABB)
	{
		return std::get<AABBData>(m_shapeData);
	}
	return AABBData{ 0.0f, 0.0f };
}
