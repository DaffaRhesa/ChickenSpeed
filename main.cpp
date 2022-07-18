#include "Main.h"

using namespace Engine;

Main::Main(Setting* setting) :Engine::Game(setting)
{

}

Main::~Main()
{
	delete music;
}

void Main::Init()
{
	inputManager->AddInputMapping("Walk Right", SDLK_RIGHT);
	inputManager->AddInputMapping("Walk Left", SDLK_LEFT);
	inputManager->AddInputMapping("Jump", SDLK_SPACE);
	inputManager->AddInputMapping("Enter", SDLK_RETURN);
	inputManager->AddInputMapping("Up", SDLK_UP);
	inputManager->AddInputMapping("Down", SDLK_DOWN);

	InitPreMenu();
	InitMenu();
	InitInGame();

	// Playing music
	music = new Music("Move-Forward.wav");
	music->SetVolume(40);
	music->Play(true);
}

void Main::InitPreMenu()
{
	backgroundPreMenuTexture = new Texture("background1.png");
	backgroundPreMenuSprite = new Sprite(backgroundPreMenuTexture, defaultSpriteShader, defaultQuad);
	backgroundPreMenuSprite->SetNumXFrames(1);
	backgroundPreMenuSprite->SetNumYFrames(1);

	textpremenu = new Text("Playon.ttf", 30, defaultTextShader);
	textpremenu->SetScale(1.0f);
	textpremenu->SetColor(255, 255, 255);
	textpremenu->SetPosition(setting->screenWidth / 2 - 150, setting->screenHeight / 2);
}

void Main::InitMenu()
{
	inputManager->AddInputMapping("Enter", SDLK_RETURN);
	//Background Menu
	backgroundMenuTexture = new Texture("background2.png");
	backgroundMenuSprite = new Sprite(backgroundMenuTexture, defaultSpriteShader, defaultQuad);
	backgroundMenuSprite->SetNumXFrames(1);
	backgroundMenuSprite->SetNumYFrames(1);

	//Button Play
	btnPlayTexture = new Texture("ButtonNormal.png");
	btnPlaySprite = new Sprite(btnPlayTexture, defaultSpriteShader, defaultQuad);
	btnPlaySprite->SetNumXFrames(1);
	btnPlaySprite->SetNumYFrames(1);
	//btnPlaySprite->SetPosition(setting->screenWidth / 2 - 70, setting->screenHeight / 2 - 10);

	//Button Exit
	btnExitTexture = new Texture("ButtonNormal.png");
	btnExitSprite = new Sprite(btnExitTexture, defaultSpriteShader, defaultQuad);
	btnExitSprite->SetNumXFrames(1);
	btnExitSprite->SetNumYFrames(1);
	//btnExitSprite->SetPosition(setting->screenWidth / 2 - 70, setting->screenHeight / 2 - 65);

	//Button Active Play
	activePlayTexture = new Texture("ButtonActive.png");
	activePlaySprite = new Sprite(activePlayTexture, defaultSpriteShader, defaultQuad);
	activePlaySprite->SetNumXFrames(1);
	activePlaySprite->SetNumYFrames(1);
	//activePlaySprite->SetPosition(setting->screenWidth / 2 - 70, setting->screenHeight / 2 - 10);

	//Button Active Exit
	activeExitTexture = new Texture("ButtonActive.png");
	activeExitSprite = new Sprite(activeExitTexture, defaultSpriteShader, defaultQuad);
	activeExitSprite->SetNumXFrames(1);
	activeExitSprite->SetNumYFrames(1);
	//activeExitSprite->SetPosition(setting->screenWidth / 2 - 70, setting->screenHeight / 2 - 65);

	//Button Text PLay
	textmenuPLAY = new Text("Playon.ttf", 80, defaultTextShader);
	textmenuPLAY->SetScale(1.0f);
	textmenuPLAY->SetColor(255, 255, 255);
	textmenuPLAY->SetPosition(setting->screenWidth / 2 - 60, setting->screenHeight / 2 + 3);

	//Button Text Exit
	textmenuEXIT = new Text("Playon.ttf", 80, defaultTextShader);
	textmenuEXIT->SetScale(1.0f);
	textmenuEXIT->SetColor(255, 255, 255);
	textmenuEXIT->SetPosition(setting->screenWidth / 2 - 60, setting->screenHeight / 2 - 90);


	//Button State
	if (btnState == ButtonState::PLAY)
	{
		textmenuPLAY->SetColor(0, 255, 0);
	}

}

void Main::InitInGame()
{

	// Background
	backgroundInGameTexture = new Texture("background3.png");
	backgroundInGameSprite = new Sprite(backgroundInGameTexture, defaultSpriteShader, defaultQuad);


	// Caracter
	monsterTexture = new Texture("ayam.png");
	monsterSprite = new Sprite(monsterTexture, defaultSpriteShader, defaultQuad);
	monsterSprite->SetNumXFrames(4);
	monsterSprite->SetNumYFrames(1);
	monsterSprite->SetAnimationDuration(150);
	monsterSprite->AddAnimation("run", 0, 3);
	monsterSprite->SetPosition(0, 70);

	//monsterSprite->AddAnimation("walk", 6, 11);
	monsterSprite->PlayAnim("run");
	//monsterSprite->SetScale(8);

	//spawnArrow
	bomTexture = new Texture("Bomb.png");
	bomSprite = new Sprite(bomTexture, defaultSpriteShader, defaultQuad);
	bomSprite->SetPosition(1200, 40);
	bomSprite->SetAnimationDuration(100);
	bomSprite->SetNumXFrames(12);
	bomSprite->SetNumYFrames(1);
	bomSprite->SetScale(2.2);
	bomSprite->SetFlipHorizontal(false);

	//score
	scoreText = new Text("Playon.ttf", 20, defaultTextShader);
	scoreText->SetPosition(46,670);
	

}

void Main::Update()
{

	//State Update
	if (state == GameState::PREMENU) {
		UpdatePreMenu();
	}
	else if (state == GameState::MENU) {
		UpdateMenu();
	}
	else if (state == GameState::GAME) {
		UpdateInGame();
	}

}

void Main::UpdatePreMenu()
{
	textpremenu->SetText("Press Enter to Continue");

	if (inputManager->IsKeyReleased("Enter"))
	{
		state = GameState::MENU;

	}
}

void Main::UpdateMenu()
{
	textmenuPLAY->SetText("PLAY");
	textmenuEXIT->SetText("EXIT");

	if (inputManager->IsKeyReleased("Up"))
	{
		btnState = ButtonState::PLAY;
		textmenuPLAY->SetColor(0, 255, 0);
		textmenuEXIT->SetColor(255, 255, 255);


	}
	else if (inputManager->IsKeyReleased("Down"))
	{
		btnState = ButtonState::EXIT;
		textmenuEXIT->SetColor(0, 255, 0);
		textmenuPLAY->SetColor(255, 255, 255);


	}
	//PLAY
	else if (inputManager->IsKeyReleased("Enter"))
	{
		if (btnState == ButtonState::PLAY) {
			state = GameState::GAME;
		}


	}
}

void Main::UpdateInGame()

{
	//Background bergerak
	float xb = backgroundInGameSprite->GetPosition().x;
	float yb = backgroundInGameSprite->GetPosition().y;
	float newX = xb - velocity * GetGameTime() * 0.05f;
	if (newX <= -2200)
		backgroundInGameSprite->SetPosition(0, yb);
	else
		backgroundInGameSprite->SetPosition(newX, yb);
	cout << "xbbbb :" << xb - velocity * GetGameTime() << endl;

	//caracter
	monsterSprite->Update(GetGameTime());
	float x = monsterSprite->GetPosition().x;
	float y = monsterSprite->GetPosition().y;
	velocity = 5;

	if (inputManager->IsKeyPressed("Walk Right")) {
		//monsterSprite->PlayAnim("run");
		//monsterSprite->SetPosition(x + velocity * GetGameTime(),
		//	y);
		x += velocity;
		monsterSprite->SetFlipHorizontal(false);

	}

	if (inputManager->IsKeyPressed("Walk Left")) {
		//monsterSprite->PlayAnim("Run");
		//monsterSprite->SetPosition(x + velocity * GetGameTime(),
		//	y);
		x -= velocity;
		monsterSprite->SetFlipHorizontal(true);

	}

	if (inputManager->IsKeyPressed("Jump") && !isJump) {
		gravity = 0.16f;
		yvelocity = 1.5;
		isJump = true;
	}

	if (y > 70) {
		yvelocity -= gravity;
	}
	else if (y < 70) {
		y = 70;
		yvelocity = 0;
		isJump = false;
	}
	y += yvelocity * GetGameTime();
	monsterSprite->SetPosition(x, y);


	//bomb
	vec2 oldPlayerPos = monsterSprite->GetPosition();
	float yPlayer = oldPlayerPos.y;
	float x = bomSprite->GetPosition().x;
	float y = bomSprite->GetPosition().y;

	if (bomb == false) {
		x -= velocity * GetGameTime();
		bomSprite->SetPosition(x, y);
		if (x <= -100) {
			bomb = true;
		}
	}
	else {
		count++;
		if (count >= 100) {
			positionSpawnY = rand() % 100 + 1;
			if (positionSpawnY <= 20) {
				bomSprite->SetPosition(1200, 70);
			}
			else if (positionSpawnY >= 21 && positionSpawnY <= 40) {
				bomSprite->SetPosition(1200, 70);
			}
			else if (positionSpawnY >= 41 && positionSpawnY <= 60) {
				bomSprite->SetPosition(1200, 70);
			}
			else if (positionSpawnY >= 61 && positionSpawnY <= 80) {
				bomSprite->SetPosition(1200, 70);
			}
			else if (positionSpawnY >= 81 && positionSpawnY <= 100) {
				bomSprite->SetPosition(1200, 70);
			}
			velocity += 0.05f;
			score += 100;
			bomb = false;
			count = 0;
		}
	}

	if (monsterSprite->GetBoundingBox()->CollideWith(bomSprite->GetBoundingBox()))
	{
		gameOn = false;
		gameOver = true;
		bomSprite->SetPosition(1200, 40);
	}
	
	//score
	if (scoreTimer += 10) {
		score += 1;
		scoreTimer = 0;
	}
	scoreText->SetText("score : " + to_string(score));
}

void Main::Render()
{
	if (state == GameState::PREMENU) {
		backgroundPreMenuSprite->Draw();
		textpremenu->Draw();
	}
	else if (state == GameState::MENU) {
		//Background
		backgroundMenuSprite->Draw();

		//Button
		if (btnState == ButtonState::PLAY)
		{
			activePlaySprite->Draw();
			btnExitSprite->Draw();
		}
		else if (btnState == ButtonState::EXIT)
		{
			btnPlaySprite->Draw();
			activeExitSprite->Draw();
		}


		//Text
		textmenuPLAY->Draw();
		textmenuEXIT->Draw();

	}
	else if (state == GameState::GAME) {
		backgroundInGameSprite->Draw();
		monsterSprite->Draw();
		bomSprite->Draw();
	
	//score
	scoreText->Draw();

}



	int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->windowTitle = "Chikcen Speed";
	setting->screenWidth = 1080;
	setting->screenHeight = 720;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 60;
	Engine::Game* game = new Engine::Main(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}