#ifndef __NANO3D__
#define __NANO3D__

// Stealing all the worst design choices from Cube since 2018

#include <windows.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <math.h>

#define LOG_INFO 0
#define LOG_INIT 1
#define LOG_ERROR 2

#define PI 3.1415927f
#define PI2 6.2831854f

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef enum {
	
	TrapKeyDown,
	TrapKeyUp,
	TrapKeyPressed
	
} NanoKeybindTrap;

typedef struct {

	float x;
	float y;
	float z;
	
} Vector3;

typedef struct {

	float x;
	float y;
	
} Vector2;

typedef struct {

	Vector3 position;
	Vector3 up;
	Vector3 right;
	Vector3 forward;
	Vector3 worldUp;
	float yaw;
	float pitch;
	float fov;
	float nearClip;
	float farClip;
	
} _NanoCamera, *NanoCamera;

typedef struct {
	
	uint hTexture;
	int width;
	int height;
	
} _NanoTexture, *NanoTexture;

typedef struct _NODE {

	void* nodeData;
	struct _NODE* nodeNext;
	
} _NODE, *NODE;

typedef struct {
	
	NODE nodes;
	int nodeCount;
	
} _NanoList, *NanoList;

typedef struct {
	
	int keyCode;
	NanoKeybindTrap bindType;
	void (*OnKey)();
	BOOL keyState;
	
} NanoKeybind;

typedef struct {
	
	byte* data;
	int length;
	
} NanoBuffer;

typedef struct { // It's the same thing as the above the fuck kinda weed you smokin Xenox take this mans keyboard away
	
	int length;
	char* string;
	
} _NanoString, *NanoString;

// Main functions
void NanoInit();
void NanoFatal(char* fatalMessage);
void NanoExpunge();
void NanoLog(char* logMessage, byte logType);
void NanoLoop();

// Util functions
void NanoSetKeyRepeat(BOOL repeatState);
NanoList NanoListCreate();
NODE NanoListPush(NanoList targetList, void* nodeData);
void NanoListMatchExpunge(NanoList targetList, void* nodeID, int dataSize);
void NanoListFree(NanoList targetList);

// Math functions
Vector3 NanoVectorAdd(Vector3 vectOne, Vector3 vectTwo);
Vector3 NanoVectorSubtract(Vector3 vectOne, Vector3 vectTwo);
float NanoRadians(float degrees);
float NanoMagnitude(Vector3 targetVector);
Vector3 NanoNormalize(Vector3 targetVector);
Vector3 NanoCross(Vector3 vectOne, Vector3 vectTwo);
float NanoClamp(float valToClamp, float valMin, float valMax);

// OpenGL functions
void NanoGLInit(int glResX, int glResY);
void NanoRender();
NanoCamera NanoCreateCamera(float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float camFOV);
void NanoSetMainCamera(NanoCamera targetCamera);
void NanoCalcCam(NanoCamera targetCamera);
void NanoCameraRotate(NanoCamera targetCamera, float camYaw, float camPitch);
NanoTexture NanoCreateTexture(byte* texData, int texWidth, int texHeight, BOOL texClamp);
// !!! TEST TEST FUCK THIS SHIT !!!
void NanoCameraForward();
void NanoCameraBackward();
void NanoCameraLeft();
void NanoCameraRight();

// I/O functions
void NanoIOInit();
void NanoIOCleanup();
void NanoRegisterKeybind(int keyCode, NanoKeybindTrap bindType, void (*keybindCallback)());
void NanoKeypress(int keyCode, BOOL isDown);
void NanoMouseMove(int xDir, int yDir);
void NanoInput();
BOOL NanoReadFile(char* filePath, NanoBuffer* fileBuffer);

// Script functions
void NanoScriptExec(NanoBuffer scriptData);
void NanoLoadScript(char* scriptPath);
void NanoConfigLoad(char* configPath);
void NanoConfigParse(NanoBuffer configData);

// String functions
NanoString NanoStringCreate(char* stringData);
void NanoStringFree(NanoString stringToFree);
NanoString* NanoStringSplit(NanoString stringToSplit, char splitDelim, int* splitCount);
NanoString NanoBufferToString(NanoBuffer bufferToConvert);

#endif
