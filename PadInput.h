#pragma once
#include <Windows.h>
#include <Xinput.h>

#include "Vector2.h"

// xinput.lib ���C���|�[�g
#pragma comment (lib,"xinput.lib")

class PadInput
{
public:
    // XINPUT_STATE �\���̂̃C���X�^���X���쐬
    XINPUT_STATE state;
    XINPUT_STATE prev;
    // �ڑ�����Ă邩
    bool isConnect = false;

public:
    // ������
    void Initialize();
    // �X�V
    void Update();

    // �������ςȂ�
    bool IsButtonDown(UINT button);
    // �������u��
    bool IsButtonTrigger(UINT button);
    // �������u��
    bool IsButtonRelease(UINT button);

    // �f�b�h�]�[���̐ݒ�
    void SetDeadZone();

    // ���X�e�B�b�N
    Vector2 GetLStick();
    // �E�X�e�B�b�N
    //Vector2 GetRStick();

    // ���g���K�[
    //int GetLTrigger(BYTE leftTrigger);
    // �E�g���K�[
    //int GetRTrigger(BYTE rightTrigger);
};