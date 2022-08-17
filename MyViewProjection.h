#pragma once
#include "ViewProjection.h"
#include <WinApp.h>

class MyViewProjection :
    public ViewProjection
{
public:
    const int win_width = WinApp::kWindowWidth;
    const int win_height = WinApp::kWindowHeight;
};

