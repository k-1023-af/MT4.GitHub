#include <Novice.h>
#include "Function.h"
#include "ImGui.h"

const char kWindowTitle[] = "LE2C_25_ファルコン_エブラハム";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//---------------------------------------
	
	int mousePosX = 0;
	int mousePosY = 0;

	Vector2 circleAPos = {(float)mousePosX, (float)mousePosY};
	float radiusA = 12.0f;

	Vector2 circleBPos = {640, 360};
	float radiusB = 20.0f;

	float speed = 6.0f;

	//---------------------------------------

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		//---------------------------------------
		

		Novice::GetMousePosition(&mousePosX, &mousePosY);

		circleAPos = {(float)mousePosX, (float)mousePosY};

		float distance = Vector2Length(circleAPos, circleBPos);

		circleBPos.x += (speed * deltaTime) * ((float)circleAPos.x - (float)circleBPos.x);
		circleBPos.y += (speed * deltaTime) * ((float)circleAPos.y - (float)circleBPos.y); 

		//---------------------------------------


	#ifdef USE_IMGUI
		
		ImGui::Begin("Interpolation Controller");
		ImGui::Text("Target: Mouse Position (Red Circle)");
		ImGui::DragFloat("Speed", &speed, 0.1f);

		ImGui::Text("Mouse Pos: (%03f, %03f)", &mousePosX, &mousePosY);
		ImGui::Text("Circle Pos: (%03f, %03f)", &circleBPos.x);
		ImGui::Text("Distance to target: %03f px", &distance);

		ImGui::End();

	#endif

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawLine(static_cast<int>(circleAPos.x), static_cast<int>(circleAPos.y), static_cast<int>(circleBPos.x), static_cast<int>(circleBPos.y), WHITE);

		Novice::DrawEllipse(static_cast<int>(circleAPos.x), static_cast<int>(circleAPos.y), (int)radiusA, (int)radiusA, (float)0.0f, RED, kFillModeSolid);
		Novice::DrawEllipse(static_cast<int>(circleBPos.x), static_cast<int>(circleBPos.y), (int)radiusB, (int)radiusB, (float)0.0f, GREEN, kFillModeSolid);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
