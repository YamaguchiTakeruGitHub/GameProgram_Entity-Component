#include "DxLib.h"
#include <vector>
#include <iostream>
#include "GameEngine/GameObject/Base/GameObject.h"
#include "GameEngine/GameObject/Character/Player/Player.h"
#include "GameEngine/GameObject/TestObject/TestObject.h"
#include "GameConstance.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);

    SetWindowText("Game");

    // 一部の関数はDxLib_Init()の前に実行する必要がある
    ChangeWindowMode(true);//true小さい表示//falseフルスクリーン

    SetGraphMode(K_WINDOW::WIDTH, K_WINDOW::HEIGHT, K_WINDOW::COLBIT);

    if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
    {
        return -1;			// エラーが起きたら直ちに終了
    }

    SetDrawScreen(DX_SCREEN_BACK);


    /*オブジェクトの宣言*/
	std::vector<std::shared_ptr<GameObject>> gameObjects;

    gameObjects.push_back(std::make_shared<Player>());
    gameObjects.push_back(std::make_shared<TestObject>());
 
    // 初期化
    for (auto& obj : gameObjects) {
        obj->Init();
    }


    // ゲームループ
    while (ProcessMessage() != -1)
    {
        // このフレームの開始時刻を覚えておく
        LONGLONG start = GetNowHiPerformanceCount();

        // 描画を行う前に画面をクリアする
        ClearDrawScreen();

        // ゲームの処理
        // PlayerとTestObjectのCollisionを取得
        auto player = std::dynamic_pointer_cast<Player>(gameObjects[0]);
        auto testObject = std::dynamic_pointer_cast<TestObject>(gameObjects[1]);
        if (player && testObject) {
            auto playerCollision = player->GetCollision();
            auto testObjectCollision = testObject->GetCollision();
            if (playerCollision && testObjectCollision) {
                // 衝突判定（pushbackや優先度は必要に応じて指定）
                playerCollision->CheckCollision(testObjectCollision, true, Prioriy::Dynamic);
				testObjectCollision->CheckCollision(playerCollision, true, Prioriy::Dynamic);
            }
        }

        int windoW = K_WINDOW::WIDTH;
        int windoH = K_WINDOW::HEIGHT;

        //画面に合わせてボックスを表示
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
        

        // 画面が切り替わるのを待つ
        ScreenFlip();

        // escキーでゲーム終了
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        // FPS60に固定する
        while (GetNowHiPerformanceCount() - start < 16667)
        {
            // 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
        }
    }

	// 終了処理
	for (auto& obj : gameObjects) {
		obj->Final();
	}

    DxLib_End();				// ＤＸライブラリ使用の終了処理

    return 0;				// ソフトの終了 

}
