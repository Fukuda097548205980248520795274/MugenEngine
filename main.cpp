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

	// UVトランスフォーム
	std::unique_ptr<UVTransform> uvTransform_ = std::make_unique<UVTransform>();
	uvTransform_->Initialize();

	// 3Dカメラ
	std::unique_ptr<Camera3D> camera3d_ = std::make_unique<Camera3D>();
	camera3d_->Initialize(mugenEngine->GetScreenWidth(), mugenEngine->GetScreenHeight());
	camera3d_->translation_.z = -5.0f;



	// ゲームループ
	while (mugenEngine->ProcessMessage())
	{
		// 描画前処理
		mugenEngine->PreDraw();

		uvTransform_->rotation_ += 0.03f;

		// ワールドトランスフォームの更新処理
		worldTransform3d_->Update();
		uvTransform_->Update();

		// カメラの更新処理
		camera3d_->Update();


		// UV球を描画する
		mugenEngine->DrawUVSphere(worldTransform3d_.get(),uvTransform_.get(), camera3d_.get(), ghUvChecker, 24, 12);


		// 描画後処理
		mugenEngine->PostDraw();
	}

	// 無限エンジンの削除
	delete mugenEngine;
	mugenEngine = nullptr;

	return 0;
}