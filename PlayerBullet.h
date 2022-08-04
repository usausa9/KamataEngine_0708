#pragma once
#include "Matrix.h"
#include <cassert>

#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "Debugtext.h"

class PlayerBullet
{
public:
	void Initialize(Model* model, const Vector3& position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	// マトリックス
	Matrix matrix_;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};