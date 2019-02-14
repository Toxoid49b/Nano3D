#include "nano3d.h"

NanoString NanoStringCreate(char* stringData) {

	NanoString newString = (NanoString)calloc(1, sizeof(_NanoString));
	newString->length = strlen(stringData);
	newString->string = stringData;
	return newString;
	
}

void NanoStringFree(NanoString stringToFree) {

	free(stringToFree->string);
	free(stringToFree);
	
}

NanoString NanoBufferToString(NanoBuffer bufferToConvert) {
	
	NanoString convStr = (NanoString)calloc(1, sizeof(_NanoString));
	convStr->length = bufferToConvert.length;
	convStr->string = (char*)bufferToConvert.data;
	
	return convStr;
	
}

NanoString* NanoStringSplit(NanoString stringToSplit, char splitDelim, int* splitCount) {

	int I = 0;
	int numTkns = 0;
	int curTkn = 0;
	int lastTkn = 0;
	
	for(I = 0; I < stringToSplit->length; I++) {	
		if(stringToSplit->string[I] == splitDelim) {
				numTkns++;
		}
	}
	numTkns++;
	
	NanoString* strSplit = (NanoString*)calloc(numTkns, sizeof(NanoString));
	for(I = 0; I < numTkns; I++) {
		strSplit[I] = (NanoString)calloc(1, sizeof(_NanoString));	
	}
	
	for(I = 0; I < stringToSplit->length; I++) {
		if(stringToSplit->string[I] == splitDelim) {
			strSplit[curTkn]->string = (char*)calloc(I - lastTkn + 1, sizeof(char));
			strSplit[curTkn]->length = (I - lastTkn);
			memcpy(strSplit[curTkn]->string, (char*)(stringToSplit->string + lastTkn), strSplit[curTkn]->length);
			lastTkn = (I + 1);
			curTkn++;
		}
	}
	strSplit[curTkn]->string = (char*)calloc(stringToSplit->length - lastTkn + 1, sizeof(char));
	strSplit[curTkn]->length = (stringToSplit->length - lastTkn);
	memcpy(strSplit[curTkn]->string, (char*)(stringToSplit->string + lastTkn), strSplit[curTkn]->length);	
	*splitCount = numTkns;
	
	return strSplit;
	
}
