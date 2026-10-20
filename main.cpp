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

	//Quaternion q1 = {2.0f, 3.0f, 4.0f, 1.0f};
	//Quaternion q2 = {1.0f, 3.0f, 5.0f, 2.0f};
	//
	//
	//Quaternion identity = IdentityQuaternion();
	//
	//Quaternion conj = Conjugate(q1);
	//
	//Quaternion inv = Inverse(q1);
	//
	//Quaternion normal = Normalize(q1);
	//
	//Quaternion mul1 = Multiply(q1, q2);
	//
	//Quaternion mul2 = Multiply(q2, q1);
	//
	//float norm = Norm(q1);

	//--------------------------------------

	Quaternion rotation = MakeRotateAxisAngleQuaternion(
	    Normalize(Vector3{ 1.0f, 0.4f, -0.2f }),
	    0.45f);

	Vector3 pointY = {2.1f, -0.9f, 1.3f};
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation);
	Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
	Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);	//do not have function yet ;_;


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

		//Novice::ScreenPrintf(0, 0,		" %.02f		%.02f	  %.02f		  %.02f	        :Identity", identity.x, identity.y, identity.z, identity.w);
		//Novice::ScreenPrintf(0, 20,		"%.02f		%.02f		%.02f	  %.02f	        :Conjugate", conj.x, conj.y, conj.z, conj.w);
		//Novice::ScreenPrintf(0, 40,		"%.02f		%.02f		%.02f	  %.02f	        :Inverse", inv.x, inv.y, inv.z, inv.w);
		//Novice::ScreenPrintf(0, 60,		" %.02f		%.02f	  %.02f		  %.02f	        :Normalize", normal.x, normal.y, normal.z, normal.w);
		//Novice::ScreenPrintf(0, 80,		" %.02f		%.02f	  %.02f		 %.02f	      :Multiply(q1, q2)", mul1.x, mul1.y, mul1.z, mul1.w);
		//Novice::ScreenPrintf(0, 100,	" %.02f		%.02f		%.02f	  %.02f	      :Multiply(q2, q1)", mul2.x, mul2.y, mul2.z, mul2.w);
		//Novice::ScreenPrintf(0, 120,	" %.02f                              :Norm", norm);


		QuaternionScreenPrintf(0, kRowHeight * 0, rotation);		// 	: rotation
		MatrixScreenPrintf(0, kRowHeight * 2, rotateMatrix);		//  : rotate Matrix
		VectorScreenPrintf(0, kRowHeight * 7, rotateByQuaternion);	//	: rotateByQuaternion
		VectorScreenPrintf(0, kRowHeight * 8, rotateByMatrix);		//	: rotateByMatrix

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
