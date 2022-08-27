#include "Collision.h"

bool CollisionRayToObject(Vector3 startRay, Vector3 endRay, WorldTransform object, float radius)
{
	// 引数からレイのベクトルを作成
	Vector3 vecRay = { endRay.x - startRay.x, endRay.y - startRay.y, endRay.z - startRay.z };
	Vector3 vecRayCopy = vecRay;
	vecRay.normalize();

	// レイの始点からオブジェクトへのベクトルを作成
	Vector3 vecObj = {
		object.translation_.x - startRay.x,
		object.translation_.y - startRay.y ,
		object.translation_.z - startRay.z };

	// 正規化したレイのベクトルとオブジェクトのベクトルの内積を求める
	float lengthN = vecRay.dot(vecObj);
	
	if (lengthN < -radius)
	{
		return false;
	}

	if (lengthN  > vecRay.length() + radius)
	{
		return false;
	}

	Vector3 vecN = {
		vecRay.x * lengthN,
		vecRay.y * lengthN,
		vecRay.z * lengthN };

	Vector3 vecNtoObj = {
		vecObj.x - vecN.x,
		vecObj.y - vecN.y,
		vecObj.z - vecN.z };

	if (vecNtoObj.length() < radius) {
		return true;
	}
	else return false;
}