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

	//--------------------------------------

	Quaternion rotation0 = MakeRotateAxisAngleQuaternion({0.71f, 0.71f, 0.0f}, 0.3f);
	Quaternion rotation1 = MakeRotateAxisAngleQuaternion({0.71f, 0.0f, 0.71f}, 3.141592f);

	Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);
	
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
		

		//---------------------------------------


	#ifdef USE_IMGUI
		
		//ImGui::Begin("Interpolation Controller");
		//ImGui::Text("Target: Mouse Position (Red Circle)");
		//ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
		//
		//ImGui::Text("Mouse Pos: (%03f, %03f)", &mousePosX, &mousePosY);
		//ImGui::Text("Circle Pos: (%03f, %03f)", &circleBPos.x);
		//ImGui::Text("Distance to target: %03f px", &distance);
		//
		//ImGui::End();

	#endif

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::ScreenPrintf(0 + kColumnWidth * 4, kRowHeight * 0, ": interpolate0, Slerp(q0, q1, 0.0f)");
		Novice::ScreenPrintf(0 + kColumnWidth * 4, kRowHeight * 1, ": interpolate1, Slerp(q0, q1, 0.3f)");
		Novice::ScreenPrintf(0 + kColumnWidth * 4, kRowHeight * 2, ": interpolate2, Slerp(q0, q1, 0.5f)");
		Novice::ScreenPrintf(0 + kColumnWidth * 4, kRowHeight * 3, ": interpolate3, Slerp(q0, q1, 0.7f)");
		Novice::ScreenPrintf(0 + kColumnWidth * 4, kRowHeight * 4, ": interpolate4, Slerp(q0, q1, 1.0f)");
		
		QuaternionScreenPrintf(0, kRowHeight * 0, interpolate0);
		QuaternionScreenPrintf(0, kRowHeight * 1, interpolate1);
		QuaternionScreenPrintf(0, kRowHeight * 2, interpolate2);
		QuaternionScreenPrintf(0, kRowHeight * 3, interpolate3);
		QuaternionScreenPrintf(0, kRowHeight * 4, interpolate4);

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
