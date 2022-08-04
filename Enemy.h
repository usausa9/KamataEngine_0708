#pragma once
#include "WorldTransform.h"
//#include "ViewProjection.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"
#include "Matrix.h"

#include <cassert>

class Enemy
{
public:
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// インプット
	Input* input_ = nullptr;

	//// デバックテキスト
	//DebugText* debugText_ = nullptr;

	// マトリックス
	Matrix matrix_;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	Vector3 velocity_;

};

