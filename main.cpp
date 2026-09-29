#include <Novice.h>
#include "Function.h"
#include "ImGui.h"


const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Spherical s{6.0f, 0.0f, -halfPi};

	const float limit = halfPi - 0.01f;
	s.radius = max(s.radius, 0.1f);
	s.theta = std::clamp(s.theta, -limit, -limit);

	
	Vector3 target = ToCartesian(s); //pos



	////////////////////////
	//page 26-29
	Vector3 offset = ToCartesian(s);
	Vector3 eye = AddVector3(target, offset);

	Vector3 worldUp{0.0f, 1.0f, 0.0f};
	Vector3 forward = Normalize(target, eye); //how to Normalize two Vector3???
	Vector3 right = Normalize(Cross(worldUp, forward));
	Vector3 up = Cross(forward, right);

	Matrix4x4 cameraMatrix{{
		{right.x,	right.y,	right.z,	0.0f},
		{up.x,		up.y,		up.z,		0.0f},
		{forward.x, forward.y,	forward.z,	0.0f},
		{eye.x,		eye.y,		eye.z,		1.0f}
	}};

	//////////////////


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


		#ifdef USE_IMGUI
		ImGui::Begin("Spherical Coordinates");
		ImGui::Text("Target: (0, 0, 0) / +Y up / Camera +Z forward");
		ImGui::InputFloat("Radius", &s.radius, 0.01f);
		ImGui::InputFloat("Theta: elevation (rad)", &theta, 0.01f);
		ImGui::InputFloat("Phi (rad)", &phi, 0.01f);
		//if (ImGui::Button("Reset Camera Transformation")) {
		//	cameraTranslate = {0.0f, 1.9f, -6.49f};
		//	cameraRotate = {0.26f, 0.0f, 0.0f};
		//}
		ImGui::Separator();
		ImGui::Text("Spherical: r = %d, theta = %d rad, phi = &d rad", &s.radius, &s.theta, &s.phi);
		ImGui::Text("Cartesian: x = %d, y = %d, z = %d"/*, &x, &y, &z*/);
		ImGui::Separator();
		ImGui::Text("Camera matrix");
		//if (ImGui::Button(isStart ? "STOP" : "START")) {
		//	isStart = !isStart;
		//	if (!isStart) {
		//		deltaTime = 0.0f;
		//		ball.velocity = {0.0f, 0.0f, 0.0f};
		//		ball.acceleration = {0.0f, 0.0f, 0.0f};
		//		ball.position = {0.8f, 1.2f, 0.03f};
		//		ball.radius = 0.05f;
		//	}
		//}
		//ImGui::DragFloat("Sphere Radius", &ball.radius, 0.01f, 0.0f, 1.0f);
		//ImGui::DragFloat3("Sphere initial position", &ball.position.x, 0.1f, -3.0f, 3.0f);
		// ImGui::DragFloat("Pendulum Length", &conicalPendulum.length, 0.1f, 0.1f, 2.0f);
		// ImGui::DragFloat3("Pendulum Anchor", &conicalPendulum.anchor.x, 0.1f, -3.0f, 3.0f);

		ImGui::Separator();

		ImGui::End();

#endif


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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
