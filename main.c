#include "nano3d.h"

int main(int argc, char* args[]) {
	
	NanoInit();
	NanoLoop();
	return 0;
	
}

void NanoInit() {
	
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	
	NanoLog("SDL", LOG_INIT);
	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_NOPARACHUTE) < 0) NanoFatal("Failed to initialize SDL");
	
	NanoLog("SDL Video", LOG_INIT);
	if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) NanoFatal("Failed initialize SDL video");
	if(SDL_SetVideoMode(800, 600, 0, SDL_OPENGL | SDL_DOUBLEBUF) == NULL) NanoFatal("Failed to initialize OpenGL");
	SDL_WM_SetCaption("Nano3D", NULL);
	
	NanoLog("SDL Input", LOG_INIT);
	SDL_WM_GrabInput(SDL_GRAB_ON);
	NanoSetKeyRepeat(FALSE);
    SDL_ShowCursor(0);
    
    NanoLog("OpenGL", LOG_INIT);
    NanoGLInit(800, 600);
    
    NanoLog("Subsystems", LOG_INIT);
    NanoIOInit();
    
    NanoLog("Loading config...", LOG_INFO);
    NanoConfigLoad("config.cfg");
    
    NanoRegisterKeybind(SDLK_ESCAPE, TrapKeyDown, NanoExpunge);
    NanoRegisterKeybind(SDLK_w, TrapKeyPressed, NanoCameraForward);
    NanoRegisterKeybind(SDLK_a, TrapKeyPressed, NanoCameraLeft);
    NanoRegisterKeybind(SDLK_s, TrapKeyPressed, NanoCameraBackward);
    NanoRegisterKeybind(SDLK_d, TrapKeyPressed, NanoCameraRight);
	
}

void NanoFatal(char* fatalMessage) {

	printf("[FATAL] %s\n", fatalMessage);
	MessageBoxA(NULL, fatalMessage, "Nano3D Fatal Error", MB_ICONERROR);
	SDL_Quit();
	exit(1);
	
}

void NanoExpunge() {

	SDL_Quit();
	NanoIOCleanup();
	exit(0);
	
}

void NanoLog(char* logMessage, byte logType) {

	printf("%s %s\n", (logType) ? "[INIT]" : (!logType) ? "[LOG]" : "[ERROR]", logMessage);
	
}

void NanoLoop() {
	
	SDL_Event curEvent;
	
	while(TRUE) {		
		
		int curMs = SDL_GetTicks();
		
		NanoInput();
		NanoRender();
		SDL_GL_SwapBuffers();
		
		while(SDL_PollEvent(&curEvent)) {
			
			switch(curEvent.type) {
			
				case SDL_QUIT: {
					NanoExpunge();
					break;	
				}
				
				case SDL_MOUSEMOTION: {
					NanoMouseMove(curEvent.motion.xrel, curEvent.motion.yrel);
					break;						
				}
				
				case SDL_KEYUP:
                case SDL_KEYDOWN: {
                	NanoKeypress(curEvent.key.keysym.sym, (curEvent.key.state == SDL_PRESSED));
                	break;
                }	
				
			}
			
		}
		
	}
	
	NanoFatal("The main loop returned, please run memtest86");
	
}
