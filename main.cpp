#include <Novice.h>
#include <math.h>
#include"MatrixFunc.h"
#include <cstdint>
const char kWindowTitle[] = "LE2B_14_サカキバラ_イブキ";



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};



	Vector3 rotate = { 0.0f,0.0f,0.0f };
	Vector3 translate = { 0.0f,0.0f,0.0f };

	Vector3 cameraPosition = { 0.0f,0.0f,-1.0f };

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };

	//時計回りで
	Vector3 kLocalVertics[3] = {};
	kLocalVertics[0] = { -0.2f,0.0f,0.0f };
	kLocalVertics[1] = { 0.0f,0.2f,0.0f };
	kLocalVertics[2] = { 0.2f,0.0f,0.0f };



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
		//左
		if (keys[DIK_A] != 0) {
			translate.x -= 0.01f;
		}
		//右
		if (keys[DIK_D] != 0) {
			translate.x += 0.01f;
		}

		//前
		if (keys[DIK_W] != 0) {
			translate.z += 0.01f;
		}
		//後ろ
		if (keys[DIK_S] != 0) {
			translate.z -= 0.01f;
		}


		//旋回
		//前
		if (keys[DIK_UP] != 0) {
			rotate.y += 0.05f;
		}
		//後ろ
		if (keys[DIK_DOWN] != 0) {
			rotate.y -= 0.05f;
		}
		Vector3 cross = Cross(v1, v2);


		//計算
		//ワールドへ
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);

		//ビュー
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(WINDOW_SIZE_WIDTH) / float(WINDOW_SIZE_HEIGHT), 0.1f, 100.0f);

		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		//ビューポート
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(WINDOW_SIZE_WIDTH), float(WINDOW_SIZE_HEIGHT), 0.0f, 1.0f);

		Vector3 screenVertices[3] = {};
		for (uint32_t i = 0; i < 3; i++) {
			Vector3 ndcVertices = Transform(kLocalVertics[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVertices, viewportMatrix);
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0, 0, cross, "Cross");


		Novice::DrawTriangle(
			int(screenVertices[0].x),
			int(screenVertices[0].y),
			int(screenVertices[1].x),
			int(screenVertices[1].y),
			int(screenVertices[2].x),
			int(screenVertices[2].y), RED, kFillModeSolid);

		Novice::ScreenPrintf(0, 15 * 1, "1.x:%f", screenVertices[0].x);
		Novice::ScreenPrintf(0, 15 * 2, "1.y:%f", screenVertices[0].y);
		Novice::ScreenPrintf(0, 15 * 3, "2.x:%f", screenVertices[1].x);
		Novice::ScreenPrintf(0, 15 * 4, "2.y:%f", screenVertices[1].y);
		Novice::ScreenPrintf(0, 15 * 5, "3.x:%f", screenVertices[2].x);
		Novice::ScreenPrintf(0, 15 * 6, "3.y:%f", screenVertices[2].y);

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
