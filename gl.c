#include "nano3d.h"

static NanoTexture errTexture;
static NanoCamera mainCamera;

void NanoGLInit(int glResX, int glResY) {

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glViewport(0, 0, glResX, glResY);
	glClearColor(0.19f, 0.30f, 0.47f, 1);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	
	// Create default camera
	NanoSetMainCamera(NanoCreateCamera(0.0f, 0.0f, -6.0f, 0.0f, 0.0f, 0.0f, 60.0f));
	
	// Setup ambient light
	float ambLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, (float*)&ambLight);	
	
	// Create default texture
	byte errTex[] = {
		0, 0, 0, 0,
		255, 0, 255, 0,
		255, 0, 255, 0,
		0, 0, 0, 0
	};
	errTexture = NanoCreateTexture((byte*)&errTex, 2, 2, FALSE);

}

void NanoRender() {
	
	if(!mainCamera) return;
		
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	
	glLoadIdentity();
	Vector3 lookTarget = NanoVectorAdd(mainCamera->position, mainCamera->forward);
	gluLookAt(mainCamera->position.x, mainCamera->position.y, mainCamera->position.z, lookTarget.x, lookTarget.y, lookTarget.z, mainCamera->up.x, mainCamera->up.y, mainCamera->up.z);
	
	
	
	//glBindTexture(GL_TEXTURE_2D, errTexture->hTexture);
	//gluSphere(testSphere, 1.0f, 12, 12);
	
}

void NanoSetMainCamera(NanoCamera targetCamera) {

	mainCamera = targetCamera;	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(mainCamera->fov, (float)800 / (float)600, mainCamera->nearClip, mainCamera->farClip);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

NanoCamera NanoCreateCamera(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float camFOV) {

	NanoCamera newCam = (NanoCamera)calloc(1, sizeof(_NanoCamera));
	newCam->position.x = xPos;
	newCam->position.y = yPos;
	newCam->position.z = zPos;
	newCam->up.y = 1.0f;
	newCam->worldUp = newCam->up;
	newCam->forward.z = -1.0f;
	newCam->fov = camFOV;	
	newCam->yaw = 90.0f;
	newCam->pitch = 0.0f;
	newCam->nearClip = 0.1f;
	newCam->farClip = 128.0f;
	
	NanoCalcCam(newCam);
	
	return newCam;
	
}

void NanoCalcCam(NanoCamera targetCamera) {

	Vector3 cFront;
	cFront.x = cos(NanoRadians(targetCamera->yaw)) * cos(NanoRadians(targetCamera->pitch));
	cFront.y = sin(NanoRadians(targetCamera->pitch));
	cFront.z = sin(NanoRadians(targetCamera->yaw)) * cos(NanoRadians(targetCamera->pitch));
	cFront = NanoNormalize(cFront);
	targetCamera->forward = cFront;
	targetCamera->right = NanoNormalize(NanoCross(targetCamera->forward, targetCamera->worldUp));
	targetCamera->up = NanoNormalize(NanoCross(targetCamera->right, targetCamera->forward));
	
}

void NanoCameraRotate(NanoCamera targetCamera, float camYaw, float camPitch) {

	if(targetCamera == NULL) targetCamera = mainCamera;
	targetCamera->yaw = NanoClamp(targetCamera->yaw + camYaw, -360.0f, 360.0f);
	targetCamera->pitch = NanoClamp(targetCamera->pitch + camPitch, -60.0f, 60.0f);
	NanoCalcCam(targetCamera);	
	
}

NanoTexture NanoCreateTexture(byte* texData, int texWidth, int texHeight, BOOL texClamp) {
	
	uint hTex;
	glGenTextures(1, &hTex);
	glBindTexture(GL_TEXTURE_2D, hTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texClamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texClamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	NanoTexture newTex = (NanoTexture)calloc(1, sizeof(_NanoTexture));
	newTex->hTexture = hTex;
	newTex->width = texWidth;
	newTex->height = texHeight;
	
	return newTex;
	
}

void NanoCameraForward() { // Test
	
	mainCamera->position = NanoVectorAdd(mainCamera->position, mainCamera->forward);
	
}

void NanoCameraBackward() { // Test
	
	mainCamera->position = NanoVectorSubtract(mainCamera->position, mainCamera->forward);
	
}

void NanoCameraLeft() { // Test

	mainCamera->position = NanoVectorSubtract(mainCamera->position, mainCamera->right);
	
}

void NanoCameraRight() { // Test
	
	mainCamera->position = NanoVectorAdd(mainCamera->position, mainCamera->right);
	
}
