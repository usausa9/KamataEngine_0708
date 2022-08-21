#include "MyViewProjection.h"

void MyViewProjection::UpdateMatrixAsOrtho()
{
	UpdateMatrix(); // ViewProjection.h

	matProjection = Matrix4::OrthoGraphicProjection(win_width, win_height, nearZ, farZ);
}
