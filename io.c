#include "nano3d.h"

static NanoList activeBinds;

void NanoIOInit() {
	
	activeBinds = NanoListCreate();
	
}

void NanoIOCleanup() {

	if(activeBinds) NanoListFree(activeBinds);
	
}

void NanoKeypress(int keyCode, BOOL isDown) {
	
	if(!activeBinds->nodeCount) return;
	
	NODE nextNode = activeBinds->nodes;
	NODE currentNode;
	NanoKeybind curBind;
	
	while(nextNode != NULL) {
		
		currentNode = nextNode;
		nextNode = currentNode->nodeNext;
		curBind = *(NanoKeybind*)(currentNode->nodeData);
		if(curBind.keyCode == keyCode) {
			((NanoKeybind*)(currentNode->nodeData))->keyState = isDown;
			if(curBind.bindType == TrapKeyDown && isDown) curBind.OnKey();
			if(curBind.bindType == TrapKeyUp && !isDown) curBind.OnKey();			
		}
			
	}
	
}

void NanoMouseMove(int xDir, int yDir) {

	NanoCameraRotate(NULL, (xDir * 0.25f), -(yDir * 0.2f));
	
}

void NanoRegisterKeybind(int keyCode, NanoKeybindTrap bindType, void (*keybindCallback)()) {
	
	NanoKeybind* newBind = (NanoKeybind*)calloc(1, sizeof(NanoKeybind));
	newBind->keyCode = keyCode;
	newBind->bindType = bindType;
	newBind->OnKey = keybindCallback;
	newBind->keyState = FALSE;
	
	NanoListPush(activeBinds, newBind);
	
}

void NanoInput() {
	
	if(!activeBinds->nodeCount) return;
	
	NODE nextNode = activeBinds->nodes;
	NODE currentNode;
	NanoKeybind curBind;
	
	while(nextNode != NULL) {
		
		currentNode = nextNode;
		nextNode = currentNode->nodeNext;
		curBind = *(NanoKeybind*)(currentNode->nodeData);
		if(curBind.bindType == 2 && curBind.keyState) {
			curBind.OnKey();
		}
			
	}
	
}

BOOL NanoReadFile(char* filePath, NanoBuffer* fileBuffer) {

	FILE* hFile = fopen(filePath, "rb");
	if(!hFile) return FALSE;
	
	fseek(hFile, 0, SEEK_END);
	int fSize = ftell(hFile);
	rewind(hFile);
	
	byte* fileDat = (byte*)malloc(fSize);
	if(!fread(fileDat, sizeof(byte), fSize, hFile)) { fclose(hFile); return FALSE; }
	fclose(hFile);
	
	fileBuffer->data = fileDat;
	fileBuffer->length = fSize;
	
	return TRUE;
	
}
