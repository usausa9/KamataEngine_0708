#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <WinApp.h>

class MyViewProjection :
    public ViewProjection
{
public:
    void UpdateMatrixAsOrtho();

private:
    const int win_width = WinApp::kWindowWidth;
    const int win_height = WinApp::kWindowHeight;
};

