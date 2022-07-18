#ifndef MAIN_H
#define MAIN_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Input.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"

namespace Engine {
	const enum GameState {
		PREMENU,
		MENU,
		GAME,
		PAUSE
	};

	const enum ButtonState {
		PLAY,
		EXIT
	};

	class Main :public Engine::Game {
	public:
		Main(Setting* setting);
		~Main();
		virtual void Init();
		virtual void Update();
		virtual void Render();

		void InitPreMenu();
		void InitMenu();
		void InitInGame();
		void InitPause();

		void UpdatePreMenu();
		void UpdateMenu();
		void UpdateInGame();
		void UpdatePause();


	private:
		GameState state = GameState::PREMENU;
		ButtonState btnState = ButtonState::PLAY;

		Engine::Texture* monsterTexture;
		Engine::Sprite* monsterSprite;

		Engine::Texture* backgroundPreMenuTexture;
		Engine::Sprite* backgroundPreMenuSprite;

		Engine::Texture* backgroundMenuTexture;
		Engine::Sprite* backgroundMenuSprite;

		Engine::Texture* backgroundInGameTexture;
		Engine::Sprite* backgroundInGameSprite;

		//Menu Button
		Engine::Texture* btnPlayTexture;
		Engine::Sprite* btnPlaySprite;
		Engine::Texture* btnExitTexture;
		Engine::Sprite* btnExitSprite;

		//Button Active Menu
		Engine::Texture* activePlayTexture;
		Engine::Sprite* activePlaySprite;
		Engine::Texture* activeExitTexture;
		Engine::Sprite* activeExitSprite;

		Text* textpremenu = NULL;
		Text* textmenuPLAY = NULL;
		Text* textmenuEXIT = NULL;

		bool isJump = false;

		//score
		Text* scoreText = NULL;
		float scoreTimer;
		int score;

		//bom
		Sprite* bomSprite = NULL;
		Texture* bomTexture = NULL;
		bool bomb = false;
		int count;
		/*int onButton;*/

		float velocity, Yjump;
		bool preMenu;
		int onButton;
		int positionSpawnY;

		Music* music;
		float gravity, yvelocity;
		
		bool menu = true;
		bool gameOn = false;
		bool gameOver = false;

	};
}
#endif