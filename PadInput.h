#pragma once
#include <Windows.h>
#include <Xinput.h>

#include "Vector2.h"

// xinput.lib をインポート
#pragma comment (lib,"xinput.lib")

class PadInput
{
public:
    // XINPUT_STATE 構造体のインスタンスを作成
    XINPUT_STATE state;
    XINPUT_STATE prev;
    // 接続されてるか
    bool isConnect = false;

public:
    // 初期化
    void Initialize();
    // 更新
    void Update();

    // 押しっぱなし
    bool IsButtonDown(UINT button);
    // 押した瞬間
    bool IsButtonTrigger(UINT button);
    // 離した瞬間
    bool IsButtonRelease(UINT button);

    // デッドゾーンの設定
    void SetDeadZone();

    // 左スティック
    Vector2 GetLStick();
    // 右スティック
    //Vector2 GetRStick();

    // 左トリガー
    //int GetLTrigger(BYTE leftTrigger);
    // 右トリガー
    //int GetRTrigger(BYTE rightTrigger);
};