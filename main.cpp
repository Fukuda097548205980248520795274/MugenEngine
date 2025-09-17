#include "Engine/Include/MugenEngine.h"

// Windowsアプリでの main関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 無限エンジンの生成と初期化
	MugenEngine* mugenEngine = new MugenEngine();
	mugenEngine->Initialize(1280, 720, "LE2A_11_フクダ_ソウワ");



	// uvChecker
	uint32_t ghUvChecker = mugenEngine->LoadTexture("./Resources/Textures/uvChecker.png");

	// ワールドトランスフォーム3D
	std::unique_ptr<WorldTransform3D> worldTransform3d_ = std::make_unique<WorldTransform3D>();
	worldTransform3d_->Initialize();

	// 3Dカメラ
	std::unique_ptr<Camera3D> camera3d_ = std::make_unique<Camera3D>();
	camera3d_->Initialize(mugenEngine->GetScreenWidth(), mugenEngine->GetScreenHeight());
	camera3d_->translation_.z = -5.0f;

	// ワールドトランスフォーム2D
	std::unique_ptr<WorldTransform2D> worldTransform2d_ = std::make_unique<WorldTransform2D>();
	worldTransform2d_->Initialize();

	// 2Dカメラ
	std::unique_ptr<Camera2D> camera2d_ = std::make_unique<Camera2D>();
	camera2d_->Initialize(mugenEngine->GetScreenWidth(), mugenEngine->GetScreenHeight());



	// ゲームループ
	while (mugenEngine->ProcessMessage())
	{
		// 描画前処理
		mugenEngine->PreDraw();

		worldTransform3d_->rotation_.y += 0.03f;

		// ワールドトランスフォームの更新処理
		worldTransform3d_->Update();
		worldTransform2d_->Update();

		// カメラの更新処理
		camera2d_->Update();
		camera3d_->Update();


		// 三角形を描画する
		mugenEngine->DrawSphere(worldTransform3d_.get(), camera3d_.get(), ghUvChecker, 32, 16);

		// スプライトを描画する
		mugenEngine->DrawSprite(worldTransform2d_.get(), camera2d_.get(), ghUvChecker);


		// 描画後処理
		mugenEngine->PostDraw();
	}

	// 無限エンジンの削除
	delete mugenEngine;
	mugenEngine = nullptr;

	return 0;
}