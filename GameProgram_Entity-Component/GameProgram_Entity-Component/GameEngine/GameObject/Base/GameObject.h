#pragma once
#include "../../Entity/Entity.h"

class GameObject : public Entity
{
private:
	int m_objectID;//�Q�[���I�u�W�F�N�g��ID

public:
	GameObject() {};
	~GameObject() = default;

	virtual void Init() = 0; // ����������
	virtual void Update() = 0; // �X�V����
	virtual void Draw() = 0; // �`�揈��
	virtual void Final() = 0; // �I������

	void SetObjectID(int _objectID) { m_objectID = _objectID; }
	int GetObjectID() const { return m_objectID; }

};

