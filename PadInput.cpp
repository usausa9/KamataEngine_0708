#include "PadInput.h"

void PadInput::Initialize()
{
    ZeroMemory(&state, sizeof(XINPUT_STATE));  
    ZeroMemory(&prev, sizeof(XINPUT_STATE));

    DWORD result;
    result = XInputGetState(0, &state);

    if (result == ERROR_SUCCESS)
    {
        isConnect = true;
    }
    else
    {
        isConnect = false;
    }
}

void PadInput::Update()
{
    prev = state;

    XInputGetState(0, &state);
    SetDeadZone();

}

bool PadInput::IsButtonDown(UINT button)
{
    if (state.Gamepad.wButtons & button)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PadInput::IsButtonTrigger(UINT button)
{
    if (state.Gamepad.wButtons == button && prev.Gamepad.wButtons != button)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PadInput::IsButtonRelease(UINT button)
{
    if (state.Gamepad.wButtons != button && prev.Gamepad.wButtons == button)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void PadInput::SetDeadZone()
{
    if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
        state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
        (state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
        state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
    {
        state.Gamepad.sThumbLX = 0;
        state.Gamepad.sThumbLY = 0;
    }
}

Vector2 PadInput::GetLStick()
{
    SHORT x = state.Gamepad.sThumbLX;
    SHORT y = state.Gamepad.sThumbLY;

    return Vector2(static_cast<float>(x) / 32768, static_cast<float>(y) / 32768);
   
}