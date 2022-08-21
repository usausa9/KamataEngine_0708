#include "Matrix4.h"

void Matrix4::IdentityMatrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j = i)
			{
				m[j][i] = 1;
			}
			else
			{
				m[j][i] = 0;
			}
		}
	}
}

Matrix4 Matrix4::OrthoGraphicProjection(int winWidth, int winHeight, float nearZ, float farZ)
{
	return Matrix4(
	2.0f/ winWidth, 0, 0, 0,
	0, 2.0f / winHeight, 0, 0,
	0, 0, 1/(farZ - nearZ), 0,
	-1, -1, nearZ/(nearZ - farZ), 1);
}