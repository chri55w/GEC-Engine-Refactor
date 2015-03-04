#include "GameState.h"
#include "Config.h"
#include "World.h"
#include "SoundManager.h"
#include "GUI.h"
#include <functional>


CGameState::CGameState() {
}


CGameState::~CGameState() {
}

void CGameState::onCreate() {
	//setup the game state 
	//create sprites for entities
	VIS.createSprite("sky.png", "sky", CRectangle(0, 1024, 0, 512), CRectangle(0, 768, 0, 448));
	VIS.createSprite("clouds.png", "clouds", CRectangle(0, 2048, 0, 256), CRectangle(0, 2048, 0, 448));
	VIS.createSprite("mountains.png", "mountains", CRectangle(0, 1024, 0, 256), CRectangle(0, 791, 0, 448));
	VIS.createSprite("city.png", "city", CRectangle(0, 1024, 0, 512), CRectangle(0, 768, 0, 448));
	VIS.createSprite("ground.png", "ground", CRectangle(0, 1024, 0, 256), CRectangle(0, 768, 0, 512));
	VIS.createSprite("character.png", "player", CRectangle(0, 64, 0, 1024), CRectangle(0, 64, 0, 64));
	/*
	//create backgrounds using scroll data or parrallax data.
	WORLD.createBackground("sky", 0.0, 0.0, 768, 448, false);
	WORLD.createBackground("clouds", 0.0, -75.0, 2048, 256, true, CEnum::LEFT, 1.0);
	WORLD.createBackground("city", 150.0f, 200.0f, 698, 321, true, 0.4f);
	WORLD.createBackground("mountains", 0.0f, 270.0f, 791, 448, true, 0.7f);
	WORLD.createBackground("ground", 0.0f, 325.0f, 791, 448, true, 1.0f);
	*/
	//add all sounds for later use
	AUDIO.addSound("jump.wav", CEnum::WAV, "jumping");
	AUDIO.addSound("gameStateBackground.wav", CEnum::WAV, "background");

	//Create containers, graphics and buttons for user interaction on the GUI
	stateGui->addContainer("healthBar", (VIS.getScreenWidth() / 2) - 50.0f, 10.0);
	stateGui->addContainerGraphic("healthBar", "healthbar.png", "healthBar", CRectangle(0, 128, 0, 256), CRectangle(0, 100, 0, 18), 0.0, 0.0);
	stateGui->addContainerButton("healthBar", "healthPack.png", "healthPack1", CRectangle(0, 16, 0, 32), new CRectangle(0, 14, 0, 14), 11.0, 16.0, CEnum::buttonName::HEALTHPACK, true);
	stateGui->addContainerButton("healthBar", "healthPack.png", "healthPack2", CRectangle(0, 16, 0, 32), new CRectangle(0, 14, 0, 14), 33.0, 16.0, CEnum::buttonName::HEALTHPACK, true);
	stateGui->addContainerButton("healthBar", "healthPack.png", "healthPack3", CRectangle(0, 16, 0, 32), new CRectangle(0, 14, 0, 14), 55.0, 16.0, CEnum::buttonName::HEALTHPACK, true);
	stateGui->addContainerButton("healthBar", "healthPack.png", "healthPack4", CRectangle(0, 16, 0, 32), new CRectangle(0, 14, 0, 14), 77.0, 16.0, CEnum::buttonName::HEALTHPACK, true);

	stateGui->addContainer("volume", 738.0, 5.0);
	stateGui->addContainerButton("volume", "mute.png", "muteBttn", CRectangle(0, 32, 0, 64), new CRectangle(0, 25, 0, 20), 0.0, 0.0, CEnum::buttonName::MUTE, true);

	updateHealthPackGUI();

	//Create world entites
	WORLD.createPlayer("player", 50.0f, 50.0f, new CRectangle(0, 64, 0, 64), new CRectangle(17, 47, 10, 64), 100, true, true);
	//Add world Entity animations
	WORLD.addEntityAnimID("player", "walkLeft", SIM.newAnimation(std::vector < int > {0, 1, 2, 3}));
	WORLD.addEntityAnimID("player", "walkRight", SIM.newAnimation(std::vector < int > {4, 5, 6, 7}));
	int firstID = SIM.newAnimation(std::vector < int > {9, 10});
	WORLD.addEntityAnimID("player", "jump", firstID);
	WORLD.addEntityAnimID("player", "startJump", SIM.newAnimation(std::vector < int > {8, 9}, firstID));
	WORLD.setEntityAnim("player", "walkRight");

	//create hidden / non-rendered entities for data processing (collision etc)
	WORLD.createHiddenEntity("GroundCollision", 0.0f, 375.0f, new CRectangle(0, 768, 0, 73));
	WORLD.createHiddenEntity("leftBarrier", -25.0f, 0.0f, new CRectangle(0, 26, 0, 448));
	WORLD.createHiddenEntity("rightBarrier", 767.0f, 0.0f, new CRectangle(0, 26, 0, 448));

	//set the desired framerate
	SIM.setFrameRate(5);

}
//Clean up state
void CGameState::onDestroy() {
	delete stateGui;
}
//when re-entering this state (after switching etc)
void CGameState::onEnter() {

}
//when leaving this state to switch to another etc
void CGameState::onExit() {

}
//on the render cycle run this function and render all images for this state
void CGameState::onRender() {
	RENDERQUEUE.pushToQueue("blah", 0, 0, 0, 0);
	VIS.clearScreenGrey(0);
	WORLD.renderWorld();
	stateGui->renderGUI();
	
}
//update everything for this state.
void CGameState::onUpdate() {

	WORLD.update();
	std::vector <CInput::mouseClick_> mouseClicks = INPUT.getMouseClicks();
	if (mouseClicks.size() > 0) {
		CEnum::buttonName buttonClicked = stateGui->checkContainerButtons(mouseClicks[0].x_pos, mouseClicks[0].y_pos);
		if (buttonClicked != CEnum::buttonName::BUTTON_NONE) {
			onButton(buttonClicked);
		}
	}
}
//check responses to button presses
void CGameState::onButton(CEnum::buttonName buttonClick) {
	switch (buttonClick) {
		case CEnum::buttonName::QUIT:
			HAPI->Close();
			break;
		case CEnum::buttonName::STARTGAME:
			break;
		case CEnum::buttonName::HEALTHPACK:
			if (healthpacks > 0) {
				healthpacks--;
				updateHealthPackGUI();
			}
			break;
		case CEnum::buttonName::MUTE:
			bool muted = AUDIO.getMuted();
			if (muted) {
				stateGui->updateElmentFrame("volume", "muteBttn", 0);
				AUDIO.setMute(0);
			} else {
				stateGui->updateElmentFrame("volume", "muteBttn", 1);
				AUDIO.setMute(1);
			}
			break;
	}
}
//update health pack data - to be later moved to more suitable location (player?)
void CGameState::updateHealthPackGUI() {
	int i = 1;
	for (i = 1; i <= healthpacks; i++) {
		stateGui->updateElmentFrame("healthBar", "healthPack" + std::to_string(i), 0);
	}
	if (i <= 4) {
		for (i; i <= 4; i++) {
			stateGui->updateElmentFrame("healthBar", "healthPack" + std::to_string(i), 1);

		}
	}
}