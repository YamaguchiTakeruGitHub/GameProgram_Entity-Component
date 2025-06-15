#include "DxLib.h"
#include <vector>
#include <iostream>
#include "GameEngine/GameObject/Base/GameObject.h"
#include "GameEngine/GameObject/Character/Player/Player.h"
#include "GameEngine/GameObject/TestObject/TestObject.h"
#include "GameConstance.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    SetWindowText("Game");

    // �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
    ChangeWindowMode(true);//true�������\��//false�t���X�N���[��

    SetGraphMode(K_WINDOW::WIDTH, K_WINDOW::HEIGHT, K_WINDOW::COLBIT);

    if (DxLib_Init() == -1)		// �c�w���C�u��������������
    {
        return -1;			// �G���[���N�����璼���ɏI��
    }

    SetDrawScreen(DX_SCREEN_BACK);


    /*�I�u�W�F�N�g�̐錾*/
	std::vector<std::shared_ptr<GameObject>> gameObjects;

    gameObjects.push_back(std::make_shared<Player>());
    gameObjects.push_back(std::make_shared<TestObject>());
 
    // ������
    for (auto& obj : gameObjects) {
        obj->Init();
    }


    // �Q�[�����[�v
    while (ProcessMessage() != -1)
    {
        // ���̃t���[���̊J�n�������o���Ă���
        LONGLONG start = GetNowHiPerformanceCount();

        // �`����s���O�ɉ�ʂ��N���A����
        ClearDrawScreen();

        // �Q�[���̏���
        // Player��TestObject��Collision���擾
        auto player = std::dynamic_pointer_cast<Player>(gameObjects[0]);
        auto testObject = std::dynamic_pointer_cast<TestObject>(gameObjects[1]);
        if (player && testObject) {
            auto playerCollision = player->GetCollision();
            auto testObjectCollision = testObject->GetCollision();
            if (playerCollision && testObjectCollision) {
                // �Փ˔���ipushback��D��x�͕K�v�ɉ����Ďw��j
                playerCollision->CheckCollision(testObjectCollision, true, Prioriy::Dynamic);
				testObjectCollision->CheckCollision(playerCollision, true, Prioriy::Dynamic);
            }
        }

        int windoW = K_WINDOW::WIDTH;
        int windoH = K_WINDOW::HEIGHT;

        //��ʂɍ��킹�ă{�b�N�X��\��
        for (int y = 0; y < (windoH / 10); y++)
        {
            for (int x = 0; x < (windoW / 10); x++)
            {
                DrawBox(x * (windoW / 10), y * (windoH / 10), windoW / 10 * x + (windoW / 10), windoH / 10 * y + (windoH / 10), 0xffffff, false);
            }
        }

		for (auto& obj : gameObjects) {
			obj->Update();
			obj->Draw();
		}
        

        // ��ʂ��؂�ւ��̂�҂�
        ScreenFlip();

        // esc�L�[�ŃQ�[���I��
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        // FPS60�ɌŒ肷��
        while (GetNowHiPerformanceCount() - start < 16667)
        {
            // 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
        }
    }

	// �I������
	for (auto& obj : gameObjects) {
		obj->Final();
	}

    DxLib_End();				// �c�w���C�u�����g�p�̏I������

    return 0;				// �\�t�g�̏I�� 

}
