#include <Novice.h>
#include "Function.h"
#include "ImGui.h"

float phi = 0.0f;
float theta = 0.0f;


const char kWindowTitle[] = "LE2C_25_ファルコン_エブラハム";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	
	//---------------------------------------
	const float limit = halfPi - 0.01f;
	
	Spherical s{6.0f, 0.0f, -halfPi};
	
	Vector3 target = {0.0f, 0.0f, 0.0f};

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
		s.radius = max(s.radius, 0.1f);
		s.theta = std::clamp(s.theta, -limit, limit);

		Vector3 offset = ToCartesian(s);
		Vector3 eye = AddVector3(target, offset); 

		Vector3 worldUp{0.0f, 1.0f, 0.0f};

		Vector3 forward = Normalize(Vector3{target.x - eye.x, target.y - eye.y, target.z - eye.z});

		Vector3 right = Normalize(Cross(worldUp, forward));

		//float rightLength = std::sqrt(Dot(right, right));
		//
		//if (rightLength < 1e-6f) {
		//	right = Normalize(Cross(Vector3{0.0f, 0.0f, 1.0f}, forward));
		//}

		Vector3 up = Cross(forward, right);

		Matrix4x4 cameraMatrix{{
			{right.x, right.y, right.z, 0.0f},
			{up.x, up.y, up.z, 0.0f},
			{forward.x, forward.y, forward.z, 0.0f},
			{eye.x, eye.y, eye.z, 1.0f}}
        };

		//---------------------------------------


	#ifdef USE_IMGUI
		ImGui::Begin("Spherical Coordinates");
		ImGui::Text("Target: (0, 0, 0) / +Y up / Camera +Z forward");
		ImGui::InputFloat("Radius", &s.radius, 0.01f);
		ImGui::InputFloat("Theta: (azimuth rad)", &s.theta, 0.01f);
		ImGui::InputFloat("Phi (elevation rad)", &s.phi, 0.01f);
		//if (ImGui::Button("Reset Camera Transformation")) {
		//	cameraTranslate = {0.0f, 1.9f, -6.49f};
		//	cameraRotate = {0.26f, 0.0f, 0.0f};
		//}
		ImGui::Separator();


		ImGui::Text("Spherical: r = %.3f, theta = %.3f rad, phi = %.3f rad", s.radius, s.theta, s.phi);
		ImGui::Text("Cartesian: x = %.3f, y = %.3f, z = %.3f", eye.x, eye.y, eye.z);
		ImGui::Text("Forward  : (%.3f, %.3f, %.3f)", forward.x, forward.y, forward.z);
		ImGui::Separator();

		//ImGui::Text("Spherical: r = %.2f, θ = %.2f, φ = %.2f", s.radius, s.theta, s.phi);
		//ImGui::Text("Eye      : (%.2f, %.2f, %.2f)", eye.x, eye.y, eye.z);
		//ImGui::Text("Forward  : (%.2f, %.2f, %.2f)", forward.x, forward.y, forward.z);

		ImGui::Text("Camera Matrix");
		ImGui::Text("[%.3f, %.3f, %.3f, %.3f]", cameraMatrix.m[0][0], cameraMatrix.m[0][1], cameraMatrix.m[0][2], cameraMatrix.m[0][3]);
		ImGui::Text("[%.3f, %.3f, %.3f, %.3f]", cameraMatrix.m[1][0], cameraMatrix.m[1][1], cameraMatrix.m[1][2], cameraMatrix.m[1][3]);
		ImGui::Text("[%.3f, %.3f, %.3f, %.3f]", cameraMatrix.m[2][0], cameraMatrix.m[2][1], cameraMatrix.m[2][2], cameraMatrix.m[2][3]);
		ImGui::Text("[%.3f, %.3f, %.3f, %.3f]", cameraMatrix.m[3][0], cameraMatrix.m[3][1], cameraMatrix.m[3][2], cameraMatrix.m[3][3]);

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
