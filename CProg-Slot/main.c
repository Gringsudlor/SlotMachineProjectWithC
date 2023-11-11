#include "raylib.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{

	const int screenWidth = 800;
	const int screenHeight = 450;
	int page = 1, choose = 0, gender = 0, frame = 0, start_money = 50000, money = start_money;
	float x = 32.0f, y = 32.0f,timer =0.0f;
	
	srand(time(NULL));

	InitWindow(screenWidth, screenHeight, "Gring's Slotmachine!!!");	//Initialize window
	InitAudioDevice();              // Initialize audio device

	//Load model texture
	Texture2D Male = LoadTexture("sprite/GMhead.png"), BodyM = LoadTexture("sprite/Walk.png");
	Texture2D Female = LoadTexture("sprite/GFhead.png"), BodyFM = LoadTexture("sprite/GirlWalk.png");
	Texture2D Cat = LoadTexture("sprite/GChead.png"), BodyC = LoadTexture("sprite/CatWalk.png");
	Texture2D Dino = LoadTexture("sprite/DinoWalk.png");
	Texture2D Ninja = LoadTexture("sprite/ninjablack.png");
	Texture2D Ninjap = LoadTexture("sprite/ninjapink.png");
	Texture2D Santa = LoadTexture("sprite/santa.png");
	Texture2D Lose = LoadTexture("sprite/GLose.png"), losebg = LoadTexture("sprite/losebg.png");
	Texture2D Win = LoadTexture("sprite/GWin.png"), winbg = LoadTexture("sprite/winbg.png");
	Texture2D Slot = LoadTexture("sprite/Slot.png"), ZoomSlot = LoadTexture("sprite/ZoomSlot.png");
	Texture2D Symbol = LoadTexture("sprite/Symbol.png");
	Texture2D seven = LoadTexture("sprite/7.png"), bell = LoadTexture("sprite/bell.png"), bar = LoadTexture("sprite/bar.png");
	Texture2D cat = LoadTexture("sprite/cat.png"), cherry = LoadTexture("sprite/cherry.png");
	Texture2D shop = LoadTexture("sprite/shop.png");
	Texture2D cashier = LoadTexture("sprite/cashier.png");
	Texture2D casinobg = LoadTexture("sprite/casinobg.png");
	Texture2D sym[5] = { seven, bell, bar, cat, cherry };	//Create array of symbol

	//Load music
	Music theme = LoadMusicStream("audio/theme.ogg");
	Music hooray = LoadMusicStream("audio/hooray.ogg");
	Music boo = LoadMusicStream("audio/boo.ogg");

	//Load sound effect
	Sound start = LoadSound("audio/start.wav");
	Sound stop = LoadSound("audio/stop.wav");
	Sound win = LoadSound("audio/win.wav");
	
	SetTargetFPS(60);               // Set the game to run at 60 frames-per-second

	float BodyframeWidth = (float)(BodyM.width / 15);
	float FMframeWidth = (float)(BodyFM.width / 20);
	float CframeWidth = (float)(BodyC.width / 10);
	float DinoframeWidth = (float)(Dino.width / 10);
	float NinjaframeWidth = (float)(Ninja.width / 10);
	float Ninjapframewidth = (float)(Ninjap.width / 10);
	float SantaframeWidth = (float)(Santa.width / 13);
	float SymHeight = (float)(Symbol.height / 5);

	int maxFrames = (int)(BodyM.width / (int)BodyframeWidth);
	int maxFrameFM = (int)(BodyFM.width / (int)FMframeWidth);
	int maxFrameC = (int)(BodyC.width / (int)CframeWidth);
	int maxFrameDino = (int)(Dino.width / (int)DinoframeWidth);
	int maxFrameNinja = (int)(Ninja.width / (int)NinjaframeWidth);
	int maxFrameNinjap = (int)(Ninjap.width / (int)Ninjapframewidth);
	int maxFrameSanta = (int)(Santa.width / (int)SantaframeWidth);
	int maxFrameSym = (int)(Symbol.height / (int)SymHeight);

	int show_slot = 0;
	int randnum1= GetRandomValue(0, 4);
	int randnum2 = GetRandomValue(0, 4);
	int randnum3 = GetRandomValue(0, 4);
	int playing_slot = 0;
	int getwin = 0;
	int show_rand = 0;
	int startspin = 0;
	int suit = 0;

	int costmale = 0;
	int costfemale = 0;
	int costcat = 0;
	int costninja = 50000;
	int costninjap = 60000;
	int costdino = 100000;
	int costsanta = 1000000;

	int suitninbought = 0;
	int suitninpbought = 0;
	int suitdinobought = 0;
	int suitsantabought = 0;

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		
		Rectangle spriteRec = { x+30, y+40, Female.width-55, Female.height-50 };			//Create rectangle on character to check collision
		Rectangle slotRec = { screenWidth / 2, 0, Slot.width, Slot.height };				//Create rectangle on slot machine to check collision
		Rectangle shopRec = { screenWidth - 110,screenHeight / 2,shop.width,shop.height };	//Create rectangle on shop to check collision

		bool checkslot = CheckCollisionRecs(spriteRec, slotRec);	//Check collision between character and slot machine
		bool checkshop = CheckCollisionRecs(spriteRec, shopRec);	//Check collision between character and shop

		UpdateMusicStream(theme);	//Upadate music
		PlayMusicStream(theme);		//Play music
		
		BeginDrawing();		// Setup canvas (framebuffer) to start drawing

		//Choose male character
		if (IsKeyPressed(KEY_M) && choose == 0) {
			page = 2;
			choose = 1;
			gender = 1;
			suit = 1;
		}

		//Choose female character
		else if (IsKeyPressed(KEY_F) && choose == 0) {	
			page = 3;
			choose = 1;
			gender = 2;
			suit = 2;
		}

		//Choose cat
		else if (IsKeyPressed(KEY_C) && choose == 0) {
			page = 4;
			choose = 1;
			gender = 3;
			suit = 3;
		}

		//Turn to page 5 when checkslot checked
		if (checkslot){
			page = 5;
		}

		//Turn to page 6 when checkshop checked
		if (checkshop) {
			page = 6;
		}

		//Movement control of character
		if (IsKeyDown(KEY_RIGHT)) {
			x += GetFrameTime() * 300.0f;
		}
		else if (IsKeyDown(KEY_LEFT)) {
			x -= GetFrameTime() * 300.0f;
		}
		else if (IsKeyDown(KEY_UP)) {
			y -= GetFrameTime() * 300.0f;
		}
		else if (IsKeyDown(KEY_DOWN)) {
			y += GetFrameTime() * 300.0f;
		}

		//Turn from slot machine page to game page
		if (IsKeyPressed(KEY_BACKSPACE) && gender == 1 && page == 5) {
			playing_slot = 0;
			page = 2;
			show_rand = 0;
			show_slot = 0;
			x = 60;
			y = 60;
		}
		else if (IsKeyPressed(KEY_BACKSPACE) && gender == 2 && page == 5) {
			playing_slot = 0;
			page = 3;
			show_rand = 0;
			show_slot = 0;
			x = 60;
			y = 60;
		}
		else if (IsKeyPressed(KEY_BACKSPACE) && gender == 3 && page == 5) {
			playing_slot = 0;
			page = 4;
			show_rand = 0;
			show_slot = 0;
			x = 60;
			y = 60;
		}

		//Turn from game page to main page
		else if (IsKeyPressed(KEY_BACKSPACE) && (page == 2 || page == 3 || page == 4)) {
			page = 1;
			choose = 0;
		}

		//Turn from shop page to game page
		if (IsKeyPressed(KEY_BACKSPACE) && gender == 1 && page == 6) {
			page = 2;
			x = 60;
			y = 60;
		}
		else if (IsKeyPressed(KEY_BACKSPACE) && gender == 2 && page == 6) {
			page = 3;
			x = 60;
			y = 60;
		}
		else if (IsKeyPressed(KEY_BACKSPACE) && gender == 3 && page == 6) {
			page = 4;
			x = 60;
			y = 60;
		}

		//Change suit in shop page
		if (IsKeyPressed(KEY_ONE) && page == 6) {
			suit = 1;
		}
		else if (IsKeyPressed(KEY_TWO) && page == 6) {
			suit = 2;
		}
		else if (IsKeyPressed(KEY_THREE) && page == 6) {
			suit = 3;
		}
		else if (IsKeyPressed(KEY_FOUR) && page == 6) {
			money -= costninja;
			suit = 4;
			suitninbought = 1;
		}
		else if (IsKeyPressed(KEY_FIVE) && page == 6) {
			money -= costninjap;
			suit = 5;
			suitninpbought = 1;
		}
		else if (IsKeyPressed(KEY_SIX) && page == 6) {
			money -= costdino;
			suit = 6;
			suitdinobought = 1;
		}
		else if (IsKeyPressed(KEY_SEVEN) && page == 6) {
			money -= costsanta;
			suit = 7;
			suitsantabought = 1;
		}

		//Check if suit bought or not
		if (suitninbought) {
			costninja = 0;
		}
		if (suitninpbought) {
			costninjap = 0;
		}
		if (suitdinobought) {
			costdino = 0;
		}
		if (suitsantabought) {
			costsanta = 0;
		}

		//Restart to main page
		if (IsKeyPressed(KEY_BACKSPACE) && (page == 0 || page == 7)) {
			PlayMusicStream(theme);
			page = 1;
			money = start_money;
			choose = 0;
			gender = 0;
			suit = 0;
			costninja = 50000;
			costninjap = 60000;
			costdino = 100000;
			costsanta = 1000000;
			suitninbought = 0;
			suitninpbought = 0;
			suitdinobought = 0;
			suitsantabought = 0;
		}

		//Check win
		if (suitninbought == 1 && suitninpbought == 1 && suitdinobought == 1 && suitsantabought == 1) {
			page = 7;
		}

		//Check lose
		if (money <= 0) {
			page = 0;
		}

		//Loop walking
		if (x > 950) {
			x = -100;
		}
		else if (x < -100) {
			x = 950;
		}
		if (y > 600) {
			y = -200;
		}
		else if (y < -200) {
			y = 600;
		}

		//Create switch page
		switch (page)
		{
		case 0:		//Lose page

			StopMusicStream(theme);
			UpdateMusicStream(boo);
			PlayMusicStream(boo);
			ClearBackground(RAYWHITE);
			DrawTexture(losebg, 0, 0, RAYWHITE);
			DrawTexture(Lose, screenWidth / 2 - 150, screenHeight / 2 - 250, RAYWHITE);
			DrawText("You Lose!!!", 220, 320, 72, RED);
			break;

		case 1:		//Main page

			ClearBackground(RAYWHITE);
			DrawText("Gring's Slot Machine!!",20,30,72,BLACK);
			DrawText("Choose your gender.",65,300,64,BLACK);
			DrawText("Prees(m) for Male Press(f) for Female", 170, 380, 24, BLACK);			
			break;

		case 2:		//Male page

			ClearBackground(RAYWHITE);
			DrawTexture(casinobg, 0, 0, RAYWHITE);
			timer += GetFrameTime();
			if (timer >= 0.2f) {
				timer = 0.0f;
				frame += 1;
			}

			frame = frame % maxFrames;
			DrawTexture(Slot, screenWidth / 2 - 50, 0, RAYWHITE);
			DrawTexture(shop, screenWidth - 110, screenHeight / 2 - 50, RAYWHITE);

			//Male suit
			if (suit == 1) {
				frame = frame % maxFrames;
				DrawTexturePro(BodyM, 
					(Rectangle) { 
					(BodyframeWidth * frame * 2-10), 0, BodyframeWidth, (float)BodyM.height }, 
					(Rectangle) { x, y, BodyframeWidth, (float)BodyM.height }, 
					(Vector2) { 10, 0 }, 0, RAYWHITE);
			}

			//Female suit
			else if (suit == 2) {
				frame = frame % maxFrameFM;
				DrawTexturePro(BodyFM, 
					(Rectangle) { (FMframeWidth * frame * 2), 0, FMframeWidth, (float)BodyFM.height }, 
					(Rectangle) { x, y, FMframeWidth, (float)BodyFM.height }, 
					(Vector2) { 60, 10 }, 0, RAYWHITE);
			}

			//Cat suit
			else if (suit == 3) {
				frame = frame % maxFrameC;
				DrawTexturePro(BodyC, 
					(Rectangle) { (CframeWidth * frame), 0, CframeWidth, (float)BodyC.height }, 
					(Rectangle) { x, y, CframeWidth, (float)BodyC.height }, 
					(Vector2) { 60, 10 }, 0, RAYWHITE);
			}

			//Ninja suit
			else if (suit == 4) {
				frame = frame % maxFrameNinja;
				DrawTexturePro(Ninja, 
					(Rectangle) { (NinjaframeWidth * frame*2), 0, NinjaframeWidth, (float)Ninja.height }, 
					(Rectangle) { x, y, NinjaframeWidth, (float)Ninja.height }, 
					(Vector2) { 55, 0 }, 0, RAYWHITE);
			}

			//Pink ninja suit
			else if (suit == 5) {
				frame = frame % maxFrameNinjap;
				DrawTexturePro(Ninjap, 
					(Rectangle) { (Ninjapframewidth * frame*2), 0, Ninjapframewidth, (float)Ninjap.height }, 
					(Rectangle) { x, y, Ninjapframewidth, (float)Ninjap.height }, 
					(Vector2) { 35, 0 }, 0, RAYWHITE);
			}

			//Dino suit
			else if(suit == 6){
				frame = frame % maxFrameDino;
				DrawTexturePro(Dino, 
					(Rectangle) { (DinoframeWidth * frame), 0, DinoframeWidth, (float)Dino.height }, 
					(Rectangle) { x, y, DinoframeWidth, (float)Dino.height }, 
					(Vector2) { 40, -25 }, 0, RAYWHITE);
			}

			//Santa suit
			else if (suit ==7) {
				frame = frame % maxFrameSanta;
				DrawTexturePro(Santa, 
					(Rectangle) { (SantaframeWidth * frame * 2 - 20), 0, SantaframeWidth, (float)Santa.height }, 
					(Rectangle) { x, y, SantaframeWidth, (float)Santa.height }, 
					(Vector2) { 102, 5 }, 0, RAYWHITE);
			}

			//Draw male head
			DrawTexturePro(Male, 
				(Rectangle) { 0, 0, Male.width, Male.height }, 
				(Rectangle) { x, y, Male.width, Male.height }, 
				(Vector2) { 60, 85 }, 0, RAYWHITE);

			break;

		case 3:		//Female page

			ClearBackground(RAYWHITE);
			DrawTexture(casinobg, 0, 0, RAYWHITE);
			timer += GetFrameTime();
			if (timer >= 0.2f) {
				timer = 0.0f;
				frame += 1;
			}
			
			DrawTexture(Slot, screenWidth / 2 - 50, 0, RAYWHITE);
			DrawTexture(shop, screenWidth - 110, screenHeight / 2 - 50, RAYWHITE);

			if (suit == 1) {
				frame = frame % maxFrames;
				DrawTexturePro(BodyM, 
					(Rectangle) { (BodyframeWidth * frame * 2 - 10), 0, BodyframeWidth, (float)BodyM.height }, 
					(Rectangle) { x, y, BodyframeWidth, (float)BodyM.height }, 
					(Vector2) { 10, 0 }, 0, RAYWHITE);
			}

			else if (suit == 2) {
				frame = frame % maxFrameFM;
				DrawTexturePro(BodyFM, 
					(Rectangle) { (FMframeWidth * frame * 2), 0, FMframeWidth, (float)BodyFM.height }, 
					(Rectangle) { x, y, FMframeWidth, (float)BodyFM.height }, 
					(Vector2) { 60, 10 }, 0, RAYWHITE);
			}

			else if (suit == 3) {
				frame = frame % maxFrameC;
				DrawTexturePro(BodyC, 
					(Rectangle) { (CframeWidth * frame), 0, CframeWidth, (float)BodyC.height }, 
					(Rectangle) { x, y, CframeWidth, (float)BodyC.height }, 
					(Vector2) { 60, 10 }, 0, RAYWHITE);
			}

			else if (suit == 4) {
				frame = frame % maxFrameNinja;
				DrawTexturePro(Ninja, 
					(Rectangle) { (NinjaframeWidth * frame * 2), 0, NinjaframeWidth, (float)Ninja.height }, 
					(Rectangle) { x, y, NinjaframeWidth, (float)Ninja.height }, 
					(Vector2) { 55, 0 }, 0, RAYWHITE);
			}

			else if (suit == 5) {
				frame = frame % maxFrameNinjap;
				DrawTexturePro(Ninjap, 
					(Rectangle) { (Ninjapframewidth * frame * 2), 0, Ninjapframewidth, (float)Ninjap.height }, 
					(Rectangle) { x, y, Ninjapframewidth, (float)Ninjap.height }, 
					(Vector2) { 35, 0 }, 0, RAYWHITE);
			}

			else if (suit == 6) {
				frame = frame % maxFrameDino;
				DrawTexturePro(Dino, 
					(Rectangle) { (DinoframeWidth * frame), 0, DinoframeWidth, (float)Dino.height }, 
					(Rectangle) { x, y, DinoframeWidth, (float)Dino.height }, 
					(Vector2) { 40, -25 }, 0, RAYWHITE);
			}

			else if (suit == 7) {
				frame = frame % maxFrameSanta;
				DrawTexturePro(Santa, 
					(Rectangle) { (SantaframeWidth * frame * 2 - 20), 0, SantaframeWidth, (float)Santa.height }, 
					(Rectangle) { x, y, SantaframeWidth, (float)Santa.height }, 
					(Vector2) { 102, 5 }, 0, RAYWHITE);
			}

			//Draw female head
			DrawTexturePro(Female, 
				(Rectangle) { 0, 0, 200, 267 }, 
				(Rectangle) { x, y, Female.width, Female.height}, 
				(Vector2) { 60, 60 }, 0, RAYWHITE);

			break;

		case 4:		//Cat page
			ClearBackground(RAYWHITE);
			DrawTexture(casinobg, 0, 0, RAYWHITE);	
			timer += GetFrameTime();
			if (timer >= 0.2f) {
				timer = 0.0f;
				frame += 1;
			}
			
			DrawTexture(Slot, screenWidth / 2 - 50, 0, RAYWHITE);
			DrawTexture(shop, screenWidth - 110, screenHeight / 2 - 50, RAYWHITE);

			if (suit == 1) {
				frame = frame % maxFrames;
				DrawTexturePro(BodyM, 
					(Rectangle) { (BodyframeWidth * frame * 2 - 10), 0, BodyframeWidth, (float)BodyM.height }, 
					(Rectangle) { x, y, BodyframeWidth, (float)BodyM.height }, 
					(Vector2) { 10, 0 }, 0, RAYWHITE);
			}

			else if (suit == 2) {
				frame = frame % maxFrameFM;
				DrawTexturePro(BodyFM, 
					(Rectangle) { (FMframeWidth * frame * 2), 0, FMframeWidth, (float)BodyFM.height }, 
					(Rectangle) { x, y, FMframeWidth, (float)BodyFM.height }, 
					(Vector2) { 60, 10 }, 0, RAYWHITE);
			}

			else if (suit == 3) {
				frame = frame % maxFrameC;
				DrawTexturePro(BodyC, 
					(Rectangle) { (CframeWidth * frame), 0, CframeWidth, (float)BodyC.height }, 
					(Rectangle) { x, y, CframeWidth, (float)BodyC.height }, 
					(Vector2) { 60, 10 }, 0, RAYWHITE);
			}

			else if (suit == 4) {
				frame = frame % maxFrameNinja;
				DrawTexturePro(Ninja, 
					(Rectangle) { (NinjaframeWidth * frame * 2), 0, NinjaframeWidth, (float)Ninja.height }, 
					(Rectangle) { x, y, NinjaframeWidth, (float)Ninja.height }, 
					(Vector2) { 55, 0 }, 0, RAYWHITE);
			}

			else if (suit == 5) {
				frame = frame % maxFrameNinjap;
				DrawTexturePro(Ninjap, 
					(Rectangle) { (Ninjapframewidth * frame * 2), 0, Ninjapframewidth, (float)Ninjap.height }, 
					(Rectangle) { x, y, Ninjapframewidth, (float)Ninjap.height }, 
					(Vector2) { 35, 0 }, 0, RAYWHITE);
			}

			else if (suit == 6) {
				frame = frame % maxFrameDino;
				DrawTexturePro(Dino, 
					(Rectangle) { (DinoframeWidth * frame), 0, DinoframeWidth, (float)Dino.height }, 
					(Rectangle) { x, y, DinoframeWidth, (float)Dino.height }, 
					(Vector2) { 40, -25 }, 0, RAYWHITE);
			}

			else if (suit == 7) {
				frame = frame % maxFrameSanta;
				DrawTexturePro(Santa, 
					(Rectangle) { (SantaframeWidth * frame * 2 - 20), 0, SantaframeWidth, (float)Santa.height }, 
					(Rectangle) { x, y, SantaframeWidth, (float)Santa.height }, 
					(Vector2) { 102, 5 }, 0, RAYWHITE);
			}

			//Draw cat head
			DrawTexturePro(Cat, 
				(Rectangle) { 0, 0, Cat.width, Cat.height }, 
				(Rectangle) { x, y, Cat.width, Cat.height }, 
				(Vector2) { 60, 85 }, 0, RAYWHITE);

			break;

		case 5:		//Slot machine page

			playing_slot = 1;
			ClearBackground(RED);
			timer += GetFrameTime();
			if (timer >= 0.2f) {
				timer = 0.0f;
				frame += 1;
			}
			frame = frame % maxFrameSym;
			DrawTexture(ZoomSlot, screenWidth / 2 - ZoomSlot.width / 2, -60, RAYWHITE);

			if (IsKeyPressed(KEY_ENTER) && !startspin) {
				PlaySound(start);
				startspin = 1;
				show_rand = 0;
				show_slot = 1;
				money -= 100;
			}

			if (IsKeyPressed(KEY_RIGHT_SHIFT) && show_slot == 1) {
				PlaySound(stop);
				startspin = 0;
				show_rand = 1;
				show_slot = 0;
				randnum1 = rand()%5;
				randnum2 = rand()%5;
				randnum3 = rand()%5;
				getwin = 0;
			}

			if (randnum1 == 0 && randnum2 == 0 && randnum3 == 0 && !getwin) {	//seven
				PlaySound(win);
				money += 777777;
				getwin = 1;
			}
			else if (randnum1 == 1 && randnum2 == 1 && randnum3 == 1 && !getwin) {	//bell
				PlaySound(win);
				money += 10000;
				getwin = 1;
			}
			else if (randnum1 == 2 && randnum2 == 2 && randnum3 == 2 && !getwin) {	//bar
				PlaySound(win);
				money += 100000;
				getwin = 1;
			}
			else if (randnum1 == 3 && randnum2 == 3 && randnum3 == 3 && !getwin) {	//cat
				PlaySound(win);
				money += 1000000;
				getwin = 1;
			}
			else if (randnum1 == 4 && randnum2 == 4 && randnum3 == 4 && !getwin) {	//cherry
				PlaySound(win);
				money += 10000;
				getwin = 1;
			}

			DrawText(FormatText("MONEY: %d",money), 600, 20, 20, RAYWHITE);
			DrawText("Press RShift", 625, 250, 20, GOLD);
			DrawText("to Stop", 645, 280, 20, GOLD);
			DrawText("Press Enter to Spin!!!", 70, 380, 60, GOLD);

			break;

		case 6:		//Shop page

			ClearBackground(RAYWHITE);
			DrawTexture(cashier, 0, 0, RAYWHITE);
			DrawText(FormatText("(1)Cost: %d", costmale), 20, 180, 20, RAYWHITE);
			DrawText(FormatText("(2)Cost: %d", costfemale), 170, 180, 20, RAYWHITE);
			DrawText(FormatText("(3)Cost: %d", costcat), 320, 180, 20, RAYWHITE);
			DrawText(FormatText("(4)Cost: %d", costninja), 470, 180, 20, RAYWHITE);
			DrawText(FormatText("(5)Cost: %d", costninjap), 20, 380, 20, RAYWHITE);
			DrawText(FormatText("(6)Cost: %d", costdino), 170, 380, 20, RAYWHITE);
			DrawText(FormatText("(7)Cost: %d", costsanta), 320, 380, 20, RAYWHITE);
			DrawText(FormatText("MONEY: %7d", money), 600, 20, 20, RAYWHITE);

			break;

		case 7:		//Win page

			StopMusicStream(theme);
			UpdateMusicStream(hooray);
			PlayMusicStream(hooray);
			ClearBackground(RAYWHITE);
			DrawTexture(winbg, 0, 0, RAYWHITE);
			DrawTexture(Win, screenWidth / 2 - 150, screenHeight / 2 - 250, RAYWHITE);
			DrawText("You Win!!!", 270, 320, 72, GOLD);

			break;

		}

		//Show spinning slot machine' symbol
		if (show_slot && playing_slot) {		
			DrawTexturePro(Symbol, 
				(Rectangle) { 0, SymHeight* frame, (float)Symbol.width, SymHeight }, 
				(Rectangle) { 310, 310, (float)Symbol.width, SymHeight }, 
				(Vector2) { 50, 150 }, 0, RAYWHITE);
			DrawTexturePro(Symbol, 
				(Rectangle) { 0, SymHeight* frame, (float)Symbol.width, SymHeight }, 
				(Rectangle) { 410, 310, (float)Symbol.width, SymHeight }, 
				(Vector2) { 50, 150 }, 0, RAYWHITE);
			DrawTexturePro(Symbol, 
				(Rectangle) { 0, SymHeight* frame, (float)Symbol.width, SymHeight }, 
				(Rectangle) { 510, 310, (float)Symbol.width, SymHeight }, 
				(Vector2) { 50, 150 }, 0, RAYWHITE);
		}

		if (show_rand && playing_slot) {		//Show random slot' machine symbol
			DrawTexture(sym[randnum1], 260, 160, RAYWHITE);		//Draw the first symbol
			DrawTexture(sym[randnum2], 360, 160, RAYWHITE);		//Draw the second symbol
			DrawTexture(sym[randnum3], 460, 160, RAYWHITE);		//Draw the third symbol
		}

		EndDrawing();		// End canvas drawing and swap buffers (double buffering)

	}

	// Unload texture from GPU memory (VRAM)
	UnloadTexture(Male);
	UnloadTexture(BodyM);
	UnloadTexture(Female);
	UnloadTexture(BodyFM);
	UnloadTexture(Cat);
	UnloadTexture(BodyC);
	UnloadTexture(Dino);
	UnloadTexture(Ninja);
	UnloadTexture(Ninjap);
	UnloadTexture(Santa);
	UnloadTexture(Lose);
	UnloadTexture(losebg);
	UnloadTexture(Win);
	UnloadTexture(winbg);
	UnloadTexture(Slot);
	UnloadTexture(ZoomSlot);
	UnloadTexture(seven);
	UnloadTexture(bell);
	UnloadTexture(Symbol);
	UnloadTexture(bar);
	UnloadTexture(cat);
	UnloadTexture(cherry);
	UnloadTexture(shop);
	UnloadTexture(cashier);
	UnloadTexture(casinobg);

	// Unload music stream buffers from RAM
	UnloadMusicStream(theme);
	UnloadMusicStream(boo);
	UnloadMusicStream(hooray);

	//Unload sound
	UnloadSound(start);
	UnloadSound(stop);
	UnloadSound(win);

	CloseAudioDevice();         // Close audio device
	CloseWindow();        // Close window

	return 0;
}