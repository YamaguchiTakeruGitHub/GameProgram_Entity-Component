#pragma once
#include "../../Entity/Entity.h"

class GameObject : public Entity
{
private:
	int m_objectID;//ゲームオブジェクトのID

public:
	GameObject() {};
	~GameObject() = default;

	virtual void Init() = 0; // 初期化処理
	virtual void Update() = 0; // 更新処理
	virtual void Draw() = 0; // 描画処理
	virtual void Final() = 0; // 終了処理

	void SetObjectID(int _objectID) { m_objectID = _objectID; }
	int GetObjectID() const { return m_objectID; }

};

