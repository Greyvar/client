#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "common.hpp"
#include "Renderer.hpp"
#include "GameState.hpp"
#include "startup.hpp"
#include "YamlNode.hpp"
#include "NetworkManager.hpp"
#include "cvars.hpp"
#include "input/0_hid/common.hpp"
#include "input/1_bindings/common.hpp"
#include "input/2_actions/common.hpp"
#include "LTimer.hpp"

#define MAX_FPS 30
#define TICKS_PER_FRAME 1000 / MAX_FPS

bool doTheLoopyLoop = true;

void eventHandler() {
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
			case SDL_TEXTINPUT:
			case SDL_TEXTEDITING:
			case SDL_MOUSEMOTION:
			case SDL_MOUSEWHEEL:
			case SDL_JOYBUTTONDOWN: // we use the controller api
			case SDL_JOYBUTTONUP:
			case SDL_JOYDEVICEADDED: 
			case SDL_JOYAXISMOTION: // ^^
				break;

			case SDL_CONTROLLERBUTTONDOWN:
				recvGamepadButtonDown(e);
				break;
			case SDL_CONTROLLERBUTTONUP:
				recvGamepadButtonUp(e);
				break;

			case SDL_WINDOWEVENT:
				switch (e.window.event) {
					case SDL_WINDOWEVENT_SHOWN:
						cout << "Main window shown" << endl;
						// no-break
					case SDL_WINDOWEVENT_RESIZED:
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						SDL_GetWindowSize(Renderer::get().getWindow(), &Renderer::get().window_w, &Renderer::get().window_h);
						break;
					case SDL_WINDOWEVENT_MINIMIZED:
						cout << "min" << e.window.type << endl;
					case SDL_WINDOWEVENT_ENTER:
					case SDL_WINDOWEVENT_LEAVE:
						break;
					default: 
						break;
				}

				break;
			case SDL_QUIT:
				doTheLoopyLoop = false;
				return;
			case SDL_CONTROLLERAXISMOTION:
				// poll instead
				break;
			case SDL_KEYDOWN:
				recvKeydownInput(e);
				break;
			case SDL_KEYUP:
				recvKeyupInput(e);
				break;
			case SDL_AUDIODEVICEADDED:
				std::cout << "Audio device found: " << SDL_GetAudioDeviceName(e.adevice.which, e.adevice.iscapture) << std::endl;
				break;
			case SDL_CONTROLLERDEVICEADDED:
				reinitGamepads();
				break;
			default: 
				std::cout << "Unknown event: 0x" << hex << e.type << std::endl;
		}
	}
}

void mainLoopRecvInput() {
	NetworkManager::get().recvAll();

	resetKeyboard();

	eventHandler();
	
	recvKeyboardInput();
	recvGamepadInputs();
}

void mainLoopProcess() {
	NetworkManager::get().handlePacketQueue();

	lookupActionBindingForPlayerInput();
	executeActionInputs();
}

void mainLoopRender(int countedFrames, int ticks) {
	Renderer::get().renderFrame();
	Renderer::get().averageFps = countedFrames / (ticks / 1000.f);
}

void mainLoop() {
	int countedFrames = 0;

	LTimer fps;
	fps.start();

	LTimer cap;

	while (doTheLoopyLoop) {	
		cap.start();

		mainLoopRecvInput();
		mainLoopProcess();
		mainLoopRender(countedFrames, fps.getTicks());

		countedFrames++;

		int frameTicks = cap.getTicks();

		if (frameTicks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
	}
}

void startGame() {
	GameState::get().ui->scene = PLAY;
}

void pushSdlQuit() {
	std::cout << "pushSdlQuit()" << endl;

	SDL_Event e;
	e.type = SDL_QUIT;

	SDL_PushEvent(&e);
}

void initLibraries() {
	srand(time(NULL));

	SDL_Init(SDL_INIT_EVERYTHING);

	initFreetype();

	initSound();

	defaultInputBindings();
}

void processInitialCvars() {
	if (cvarIsset("server")) {
		NetworkManager::get().connectToServer(cvarGet("server"));
	}
}

void quitGame() {
	GameState::get().clear();
}

void quitLibraries() {
	quitSound();
}

int main(int argc, char* argv[]) {
	cout << "Greyvar " << endl << "-------" << endl;

	cvarInit();
	loadHomedirConfigurationFile();

	parseArguments(argc, argv);

	initLibraries();

	SDL_Window *win = SDL_CreateWindow("Greyvar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TILE_SIZE * GRID_SIZE, TILE_SIZE * GRID_SIZE, SDL_WINDOW_SHOWN);
	SDL_SetWindowResizable(win, SDL_TRUE);

	Renderer::set(win, SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

	GameState::get().loadWorld("default");

	processInitialCvars();

	mainLoop();

	SDL_DestroyWindow(win);

	quitGame();
	quitLibraries();
	SDL_Quit();

	return 0;
}

