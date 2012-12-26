#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "state.h"
#include "load.h"
#include "gamestates.h"
#define FPS 60

// Comment from linux box!!

int main(int argc, char *argv[])
{
	int start;
	int finish;

	if(init() != 0) {
		fprintf(stderr, "Initialization failed\n");
		return 1;
	}
	
	while(running == 1) {
		start = SDL_GetTicks();
		// ==============================
		// Events
		// ==============================
		switch(currentState) {
			case STATE_INTRO_TRANSITION:
				intro_transition_events();
				break;
			case STATE_INTRO:
				intro_events();
				break;
			case STATE_INTRO_TRANSITION_FADE:
				intro_transition_fade_events();
				break;
			case STATE_TITLE_TRANSITION:
				title_transition_events();
				break;
			case STATE_TITLE_FALL:
				title_fall_events();
				break;
			case STATE_TITLE_OPTIONS:
				title_options_events();
				break;
			case STATE_TITLE:
				title_events();
				break;
			case STATE_GAME:
				game_events();
				break;
		}
		
		// =============================
		// Logic
		// =============================
		switch(currentState) {
			case STATE_INTRO_TRANSITION:
				intro_transition_logic();
				break;
			case STATE_INTRO:
				intro_logic();
				break;
			case STATE_INTRO_TRANSITION_FADE:
				intro_transition_fade_logic();
				break;
			case STATE_TITLE_TRANSITION:
				title_transition_logic();
				break;
			case STATE_TITLE_FALL:
				title_fall_logic();
				break;
			case STATE_TITLE_OPTIONS:
				title_options_logic();
				break;
			case STATE_TITLE:
				title_logic();
				break;
			case STATE_GAME:
				game_logic();
				break;
		}
		
		change_state();
		
		// ============================
		// Rendering
		// ============================
		switch(currentState) {
			case STATE_INTRO_TRANSITION:
				intro_transition_render();
				break;
			case STATE_INTRO:
				intro_render();
				break;
			case STATE_INTRO_TRANSITION_FADE:
				intro_transition_fade_render();
				break;
			case STATE_TITLE_TRANSITION:
				title_transition_render();
				break;
			case STATE_TITLE_FALL:
				title_fall_render();
				break;
			case STATE_TITLE_OPTIONS:
				title_options_render();
				break;
			case STATE_TITLE:
				title_render();
				break;
			case STATE_GAME:
				game_render();
				break;
		}
		
		finish = SDL_GetTicks();
		if((1000/FPS) > (finish - start)) {
		    SDL_Delay(1000/FPS - (finish - start));
		}
	}

	quit();
	
	return 0;
}

int init()
{
	alpha = 255;
	running = 1;

	// word fall logo globals
	wTitleY = -50;
	oTitleY = -75;
	rTitleY = -100;
	dTitleY = -125;
	fTitleY = -175;
	aTitleY = -200;
	lTitleY = -225;
	l2TitleY = -250;
	wordY = 150;
	fallY = 200;

	currentState = STATE_INTRO_TRANSITION;
	nextState = STATE_NULL;

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		fprintf(stderr, "SDL Initialization failed\n %s\n", SDL_GetError());
		return 1;
	}
	
	if(TTF_Init() == -1) {
		fprintf(stderr, "SDL TTF initialization failed\n %s\n", TTF_GetError());
		return 1;
	}
	
	screen = SDL_SetVideoMode(360,640,32,SDL_HWSURFACE);
	if(screen == NULL) {
		fprintf(stderr, "Video initialization failed\n %s\n", SDL_GetError());
		return 1;
	}
	
	// changing the null value you can set an icon for when the window is
	// minimized
	SDL_WM_SetCaption("Word Fall", NULL);
	
	//SDL_WM_SetIcon will set the icon for the window.
	
	if(load_content() != 0) {
		fprintf(stderr, "File loading failed\n");
		return 1;
	}

	return 0;
}

int load_content()
{
	// ===== Intro =====
	introTransition = load_image_noalpha("assets/images/intro-transition.png");
	if(introTransition == NULL) {
		fprintf(stderr, "introTransition image not found\n%s\n", IMG_GetError());
		return 1;
	}
	
	introBackground = load_image_noalpha("assets/images/intro.png");
	if(introBackground == NULL) {
		fprintf(stderr,"Intro background image not found\n %s \n", IMG_GetError());
		return 1;
	}
	
	background = load_image_noalpha("assets/images/background.png");
	if(background == NULL) {
		fprintf(stderr, "Background image loading failed\n%s\n", IMG_GetError());
		return 1;
	}
	
	// --- CLOUDS ---
	cloud1 = load_image("assets/images/clouds.png");
	if(cloud1 == NULL) {
		fprintf(stderr, "cloud 1 loading failed\n%s\n", IMG_GetError());
		return 1;
	}
	
	cloud2 = load_image("assets/images/clouds.png");
	if(cloud2 == NULL) {
		fprintf(stderr, "cloud 2 loading failed\n%s\n", IMG_GetError());
		return 1;
	}
	
	cloud3 = load_image("assets/images/clouds.png");
	if(cloud3 == NULL) {
		fprintf(stderr, "cloud 3 loading failed\n%s\n", IMG_GetError());
		return 1;
	}
	
	// --- TITLE WORD FALL ---
	wTitle = load_image("assets/images/letters/W.png");
	if(wTitle == NULL) {
		fprintf(stderr, "w title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	oTitle = load_image("assets/images/letters/O.png");
	if(oTitle == NULL) {
		fprintf(stderr, "o title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	rTitle = load_image("assets/images/letters/R.png");
	if(rTitle == NULL) {
		fprintf(stderr, "r title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	dTitle = load_image("assets/images/letters/D.png");
	if(dTitle == NULL) {
		fprintf(stderr, "d title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	fTitle = load_image("assets/images/letters/F.png");
	if(fTitle == NULL) {
		fprintf(stderr, "f title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	aTitle = load_image("assets/images/letters/A.png");
	if(aTitle == NULL) {
		fprintf(stderr, "a title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	lTitle = load_image("assets/images/letters/L.png");
	if(lTitle == NULL) {
		fprintf(stderr, "l title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	l2Title = load_image("assets/images/letters/L.png");
	if(wTitle == NULL) {
		fprintf(stderr, "L2 title letter loading failed\n%s\n",IMG_GetError());
		return 1;
	}
	
	grass = load_image("assets/images/grass-small.png");
	if(grass == NULL) {
		fprintf(stderr, "grass loading failed\n%s\n",IMG_GetError());
		return 1;
	}

	// =========== LOADING FOR LETTERS AND CONTAINERS =================
	int i = 0;
	for(i = 0; i < 26; i++) {
		// This function converts the array number to the corresponding
		// ascii value.
		int asciiCode = i+65;
		// I really have no idea how this line works so I should probably
		// do some more invesitgating.
		char *letter = (char*)&asciiCode;
		char *location = "assets/images/letters/";
		char *png = ".png";
		char *final = malloc(sizeof(char)*strlen(location)+strlen(png)+1);
		strcpy(final, location);
		strcat(final, letter);
		strcat(final, png);
		letters[i] = load_image(final);
		if(letters[i] == NULL) {
			fprintf(stderr, "Letter loading failed\n%s\n", IMG_GetError());
			return 1;
		}
		free(final);
	}

	

	playFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(playFont == NULL) {
		fprintf(stderr, "play font loading failed\n%s\n",TTF_GetError());
		return 1;
	}
	
	optionsFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsFont == NULL) {
		fprintf(stderr, "options font loading failed\n%s\n",TTF_GetError());
		return 1;
	}

	optionsSoundFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsSoundFont == NULL) {
		fprintf(stderr, "options sound font loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	optionsSoundFontOn = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsSoundFontOn == NULL) {
		fprintf(stderr, "options sound font on loading failed\n%s\n", TTF_GetError());
		return 1;
	}

	optionsSoundFontOff = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsSoundFontOff == NULL) {
		fprintf(stderr, "options sound font off loading failed\n%s\n", TTF_GetError());
		return 1;
	}
	optionsBackFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(optionsBackFont == NULL) {
		fprintf(stderr, "options back font loading failed\n%s\n", TTF_GetError());
		return 1;
	}
	pauseFont = load_font("assets/fonts/Roboto-Bold.ttf", 36);
	if(pauseFont == NULL) {
		fprintf(stderr, "Pause font loading failed\n%s\n", TTF_GetError());
	}
	return 0;
}

void quit()
{
	//printf("I'm quitting!!\n");

	// There must be a better way to do this
	SDL_FreeSurface(background);
	SDL_FreeSurface(cloud1);
	SDL_FreeSurface(cloud2);
	SDL_FreeSurface(cloud3);
	SDL_FreeSurface(wTitle);
	SDL_FreeSurface(oTitle);
	SDL_FreeSurface(rTitle);
	SDL_FreeSurface(dTitle);
	SDL_FreeSurface(fTitle);
	SDL_FreeSurface(aTitle);
	SDL_FreeSurface(lTitle);
	SDL_FreeSurface(l2Title);
	SDL_FreeSurface(grass);
	SDL_FreeSurface(play);
	SDL_FreeSurface(options);
	SDL_FreeSurface(optionsSound);
	SDL_FreeSurface(optionsSoundOn);
	SDL_FreeSurface(optionsSoundOff);
	SDL_FreeSurface(optionsBack);
	SDL_FreeSurface(introBackground);
	SDL_FreeSurface(introTransition);
	SDL_FreeSurface(pause);
	int i;
	for(i = 0; i < 8; i++) {
		SDL_FreeSurface(container[i]);
	}
	for(i = 0; i < 27; i++) {
		SDL_FreeSurface(letters[i]);
	}
	SDL_FreeSurface(screen);

	TTF_CloseFont(playFont);
	TTF_CloseFont(optionsFont);
	TTF_CloseFont(optionsSoundFont);
	TTF_CloseFont(optionsSoundFontOn);
	TTF_CloseFont(optionsSoundFontOff);
	TTF_CloseFont(optionsBackFont);
	TTF_CloseFont(pauseFont);

	TTF_Quit();
	SDL_Quit();
}
