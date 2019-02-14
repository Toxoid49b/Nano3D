#include "nano3d.h"

void NanoLoadScript(char* scriptPath) {

	NanoBuffer scriptData;
	if(!NanoReadFile(scriptPath, &scriptData)) { NanoLog("Could not load script", LOG_ERROR); return; }
	NanoScriptExec(scriptData);
	free(scriptData.data);
	
}

void NanoScriptExec(NanoBuffer scriptData) {

	
	
}

void NanoConfigLoad(char* configPath) {

	NanoBuffer configData;
	if(!NanoReadFile(configPath, &configData)) { NanoLog("Could not load config", LOG_ERROR); return; }
	NanoConfigParse(configData);
	free(configData.data);	
	
}

void NanoConfigParse(NanoBuffer configData) {

	int cfgLineCount;
	int curLine;
	NanoString cfgLine;
	NanoString* cfgLines = NanoStringSplit(NanoBufferToString(configData), '\n', &cfgLineCount);
	
	for(curLine = 0; curLine < cfgLineCount; curLine++) {
	
		cfgLine = cfgLines[curLine];
		NanoStringFree(cfgLine);
		
	}
	
	free(cfgLines);
	
}
