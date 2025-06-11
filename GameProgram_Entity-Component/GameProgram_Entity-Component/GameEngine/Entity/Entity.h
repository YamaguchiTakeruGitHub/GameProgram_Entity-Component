#pragma once
#include "../Component/Base/Component.h"
#include "../Component/Base/Common_Component.h"

/// <summary>
/// Entity�N���X:������Component�𓮓I�ɕێ��E�Ǘ�����G���e�B�e�B�N���X
/// </summary>
class Entity
{
private:
	//�eComponent���^��������ŊǗ�(�^�� -> Component�̃|�C���^)
	std::unordered_map<std::string, std::shared_ptr<Component>> components;

protected:
	//�C�ӂ̌^T�̃R���|�[�l���g���쐬�E�ǉ�����e���v���[�g�֐�
	//�����͂��̂܂�T�̃R���X�g���N�^�ɓn��
	template<typename T, typename... Args>
	void AddComponent(Args&&... _args)
	{
		//typeid(T).name()���L�[�ɂ��ăR���|�[�l���g���i�[
		components[typeid(T).name()] = std::make_shared<T>(std::forward<Args>(_args)...);
	}

	// �^ T �̃R���|�[�l���g���擾����e���v���[�g�֐�
	// ���L�|�C���^�� dynamic_pointer_cast �ŃL���X�g���ĕԂ�
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		// �}�b�v����^���ɑΉ�����R���|�[�l���g������
		auto it = components.find(typeid(T).name());
		if (it != components.end())
		{
			// ���L�|�C���^�̃L���X�g
			return std::dynamic_pointer_cast<T>(it->second);
		}
		// ������Ȃ������ꍇ�� nullptr ��Ԃ�
		return nullptr;
	}

	void InitComponent();

	void UpdateComponent();

	void DrawComponent();

	void FinalComponent();

};

