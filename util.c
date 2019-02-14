#include "nano3d.h"

void NanoSetKeyRepeat(BOOL repeatState) {

	SDL_EnableKeyRepeat(repeatState ? SDL_DEFAULT_REPEAT_DELAY : 0, SDL_DEFAULT_REPEAT_INTERVAL);
	
}

NanoList NanoListCreate() {

	NanoList newList = (NanoList)calloc(1, sizeof(_NanoList));
	newList->nodes = NULL;
	newList->nodeCount = 0;
	
	return newList;
	
}

NODE NanoListPush(NanoList targetList, void* nodeData) {
	
	if(targetList == NULL) return NULL;
	
	NODE newNode = (NODE)calloc(1, sizeof(_NODE));
	newNode->nodeData = nodeData; 
	newNode->nodeNext = NULL;
	
	if(targetList->nodes == NULL) {
		targetList->nodes = newNode;
		targetList->nodeCount++;
		return newNode;
	}
	
	NODE nextNode = targetList->nodes;
	while(nextNode->nodeNext != NULL) nextNode = nextNode->nodeNext;
	nextNode->nodeNext = newNode;
	targetList->nodeCount++;
	return newNode;
	
}

void NanoListMatchExpunge(NanoList targetList, void* nodeID, int dataSize) {

	NODE nextNode = targetList->nodes;
	NODE currentNode;
	
	while(nextNode != NULL) {
	
		currentNode = nextNode;
		nextNode = currentNode->nodeNext;
		if(!memcmp(currentNode->nodeData, nodeID, dataSize)) {
			// Do thing
			break;	
		}
		
	}
	
}

NODE NanoListIndexOf(NanoList targetList, int nodeIndex) {

	
	
}

void NanoListFree(NanoList targetList) {

	NODE nextNode = targetList->nodes;
	NODE currentNode;
	
	while(nextNode != NULL) {
		
		currentNode = nextNode;
		nextNode = currentNode->nodeNext;		
		free(currentNode);
		
	}
	
	free(targetList);
	
}
