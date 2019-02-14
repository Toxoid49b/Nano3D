#include "nano3d.h"

Vector3 NanoVectorAdd(Vector3 vectOne, Vector3 vectTwo) {

	Vector3 addVect = {
		vectOne.x + vectTwo.x,
		vectOne.y + vectTwo.y,
		vectOne.z + vectTwo.z
	};
	return addVect;
	
}

Vector3 NanoVectorSubtract(Vector3 vectOne, Vector3 vectTwo) {
	
	Vector3 subVect = {
		vectOne.x - vectTwo.x,
		vectOne.y - vectTwo.y,
		vectOne.z - vectTwo.z
	};
	return subVect;
	
}

float NanoRadians(float degrees) {

	return (degrees * PI) / 180;
	
}

float NanoMagnitude(Vector3 targetVector) {

	return (float)sqrt((targetVector.x * targetVector.x) + (targetVector.y * targetVector.y) + (targetVector.z * targetVector.z));
	
}

Vector3 NanoNormalize(Vector3 targetVector) {

	float vMag = NanoMagnitude(targetVector);
	if(vMag == 0.0f) {
		vMag = 1.0f;
	} else {
		vMag = 1.0f / vMag;
	}
	Vector3 normVec = {
			targetVector.x * vMag,
			targetVector.y * vMag,
			targetVector.z * vMag
	};
	return normVec;
	
}

Vector3 NanoCross(Vector3 vectOne, Vector3 vectTwo) {

	Vector3 crossProd = {
		(vectOne.y * vectTwo.z) - (vectOne.z * vectTwo.y),
		(vectOne.z * vectTwo.x) - (vectOne.x * vectTwo.z),
		(vectOne.x * vectTwo.y) - (vectOne.y * vectTwo.x)
	};
	
	return crossProd;
	
}

float NanoClamp(float valToClamp, float valMin, float valMax) {

	const float tstVal = valToClamp < valMin ? valMin : valToClamp;
	return tstVal > valMax ? valMax : valToClamp;
	
}
