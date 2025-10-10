#include "MugenEngine.h"
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib, "dxcompiler.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "Mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "winmm.lib")

/// <summary>
/// デストラクタ
/// </summary>
MugenEngine::~MugenEngine()
{
	// 乱数生成の終了処理
	randomUtil_->Finalize();

	// 調整記録の終了処理
	recordSetting_->Finalize();

	// COMの終了処理
	CoUninitialize();
}

/// <summary>
/// 初期化
/// </summary>
void MugenEngine::Initialize(int32_t clientWidth, int32_t clientHeight, const std::string& title)
{
	// 出力用のディレクトリを掘る
	std::filesystem::create_directories("../build/outputs");

	// COMの初期化
	CoInitializeEx(0, COINIT_MULTITHREADED);

	// 例外が発生したときに起動する
	SetUnhandledExceptionFilter(ExportDump);

	// ログファイルの生成と初期化
	logFile_ = std::make_unique<LogFile>();
	logFile_->Initialize();

	// ウィンドウアプリケーションの生成と初期化
	winApp_ = std::make_unique<WinApp>();
	winApp_->Initialize(clientWidth, clientHeight, title);

	// クライアント領域のポインタを取得する
	kClientWidth_ = winApp_->GetClientWidthP();
	kClientHeight_ = winApp_->GetClientHeightP();

	// DirectXベースの生成と初期化
	directXBase_ = std::make_unique<DirectXBase>();
	directXBase_->Initialize(logFile_.get(), winApp_.get(), kClientWidth_, kClientHeight_);

	// 入力の生成と初期化
	input_ = std::make_unique<Input>();
	input_->Initialize(logFile_.get(), winApp_.get());

	// オーディオ格納場所の生成と初期化
	audioStore_ = std::make_unique<AudioStore>();
	audioStore_->Initialize(logFile_.get());

	// 衝突判定の生成と初期化
	collision_ = std::make_unique<Collision>();
	collision_->Initialize(this);

	// 調整記録の生成と初期化
	recordSetting_ = RecordSetting::GetInstance();

	// 乱数生成の生成と初期化
	randomUtil_ = RandomUtil::GetInstance();
	randomUtil_->Initialize();

}

/// <summary>
/// フレーム開始処理
/// </summary>
void MugenEngine::FrameStart()
{
	// 全ての入力情報を取得する
	input_->CheckInputInfo();

	// 流れていない音楽を削除する
	audioStore_->DeletePlayAudio();

	// 描画前処理
	directXBase_->PreDraw();

#ifdef _DEVELOPMENT
	// DockSpaceの作成処理
	CreateDockSpace("DockSpace");

	// 設定記録の更新処理
	recordSetting_->Update();

#endif
}

/// <summary>
/// フレーム終了処理
/// </summary>
void MugenEngine::FrameEnd()
{
	// 描画処理
	directXBase_->PostDraw();

	// 全ての入力情報をコピーする
	input_->CopyInputInfo();
}

/// <summary>
/// スプライトを描画する
/// </summary>
/// <param name="worldTransform"></param>
/// <param name="camera"></param>
/// <param name="textureHandle"></param>
void MugenEngine::DrawSprite(const WorldTransform2D* worldTransform, const Vector2& anchor, const Vector2& textureLeftTop, const Vector2& textureSize,
	const UVTransform* uvTransform, const Camera2D* camera, uint32_t textureHandle, const Vector4& color, bool isFlipX, bool isFlipY)const
{
	// ワールドビュープロジェクション行列
	Matrix4x4 worldViewProjectionMatrix = worldTransform->worldMatrix_ * camera->viewMatrix_ * camera->projectionMatrix_;

	// ビューポート変換行列
	Matrix4x4 viewportMatrix = MakeViewportMatrix4x4(0.0f, 0.0f, camera->screenWidth_, camera->screenHeight_, 0.0f, 1.0f);

	float left = -anchor.x;
	float right = 1.0f - anchor.x;
	float top = -anchor.y;
	float bottom = 1.0f - anchor.y;

	// フリップする
	if (isFlipX)
	{
		left *= -1.0f;
		right *= -1.0f;
	}

	if (isFlipY)
	{
		top *= -1.0f;
		bottom *= -1.0f;
	}

	Vector3 vertecies[4] =
	{
		Transform(Transform(Vector3(left ,top , 0.0f) , worldViewProjectionMatrix), viewportMatrix),
		Transform(Transform(Vector3(right  , top , 0.0f) , worldViewProjectionMatrix), viewportMatrix),
		Transform(Transform(Vector3(left  ,bottom , 0.0f) , worldViewProjectionMatrix), viewportMatrix),
		Transform(Transform(Vector3(right  , bottom , 0.0f) , worldViewProjectionMatrix), viewportMatrix)
	};

	directXBase_->DrawSprite(
		Vector3(vertecies[0].x, vertecies[0].y, worldTransform->translation_.z),
		Vector3(vertecies[1].x, vertecies[1].y, worldTransform->translation_.z),
		Vector3(vertecies[2].x, vertecies[2].y, worldTransform->translation_.z),
		Vector3(vertecies[3].x, vertecies[3].y, worldTransform->translation_.z),
		textureLeftTop, textureSize, uvTransform, camera, textureHandle, color);
}