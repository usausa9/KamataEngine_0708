#pragma once
#include "Vector3.h"
#include "WorldTransform.h"

bool CollisionRayToObject(Vector3 startRay, Vector3 endRay, WorldTransform object, float radius);
