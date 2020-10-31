#include "Game.h"

const int thickness = 15;
const float paddle_H = 150.0f;

Game::Game()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	,mTicksCount(0)
	,mPaddleDir(0)
	,mlsRunning(true)
{}

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0) {
		SDL_Log("SDLを初期化できません:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++(Chapter1)", //ウィンドウのタイトル
		100, //ウィンドウのx座標
		100, //ウィンドウのy座標
		1024, //ウィンドウの幅(width)
		768, //ウィンドウの高さ(height)
		0 //フラグ(設定しないときは0)
	);

	if (!mWindow) {
		SDL_Log("ウィンドウの作成に失敗しました:%s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow, //作成するレンダラーの描画対象となるウィンドウ
		-1, //デフォルトで-1ウィンドウが複数ある場合に用いる。
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	//失敗したらnullptrを返す
	if (!mRenderer) {
		SDL_Log("レンダラーの作成に失敗しました:%s", SDL_GetError());
		return false;
	}

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;

	mBallVel.x = 150.0f;
	mBallVel.y = 190.0f;

	return true;
}

void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::RunLoop() {

	while (mlsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() {
	SDL_Event event;

	//キューにイベントがあれば繰り替えす
	while (SDL_PollEvent(&event)) {

		switch (event.type) {
			//ここで各種のイベントを処理する。

			//ユーザーが「×」をクリックしたときにゲームループを止める。
		case SDL_QUIT:
			mlsRunning = false;
			break;
		}
	}

	//キーボードの状態の配列を取得する関数
	const Uint8* state = SDL_GetKeyboardState(NULL);

	//[ESC]キーが押された時もゲームループを終える
	if (state[SDL_SCANCODE_ESCAPE]) {
		mlsRunning = false;
	}

	//paddleの方向の更新。WとS両方押したら動かないようになっている。
	mPaddleDir = 0;

	if (state[SDL_SCANCODE_W]) {
		mPaddleDir -= 1;
	}
	else if (state[SDL_SCANCODE_S]) {
		mPaddleDir += 1;
	}

}

void Game::UpdateGame() {

	while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	//deltatimeは前のフレームとの時刻の差を秒に変換した値。Ticksはms単位だからs単位に直すために1000で割っている。
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	if (deltaTime < 0.05f)
	{
		deltaTime = 0.05f;
	}

	//時刻を更新(次のフレームのために)
	mTicksCount = SDL_GetTicks();

	//ToDo: ゲームワールドのオブジェクトの更新を行う。
	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime; //300.0fpixel/sでパドルは動く。

		//パドルが外に出ないようにする。
		if (mPaddlePos.y < (paddle_H / 2.0f + thickness)) {//パドルの中心位置がパドルの高さと壁を合わせたものよりも上にあるとダメ
			mPaddlePos.y = paddle_H / 2.0f + thickness;
		}
		else if (mPaddlePos.y > 768.0f - (paddle_H / 2.0f + thickness)) {
			mPaddlePos.y = 768.0f - (paddle_H / 2.0f + thickness);
		}
	}

	//Ballの位置更新
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	//Ballの衝突判定
	float diff = mPaddlePos.y - mBallPos.y;
	
	//壁との衝突
	//上壁
	if (mBallPos.y < thickness * 1.5f && mBallVel.y < 0.0f) {
		mBallVel.y = -mBallVel.y;
	}
	//右壁
	if (mBallPos.x > 1024.0f - (thickness * 1.5f) && mBallVel.x > 0.0f) {
		mBallVel.x = -mBallVel.x;
	}
	//下壁
	if (mBallPos.y > 768.0f - (thickness * 1.5f) && mBallVel.y > 0.0f) {
		mBallVel.y = -mBallVel.y;
	}
	//パドル横
	diff = diff < 0.0f ? -diff : diff;
	if (diff < paddle_H / 2.0f && mPaddlePos.x + thickness / 2.0f < mBallPos.x && mBallPos.x < mPaddlePos.x + thickness && mBallVel.x < 0.0f) {
		mBallVel.x = -mBallVel.x;
	}
	//パドル上下

}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(
		mRenderer,
		0, //R
		0, //G
		255, //B
		255 //A : 透明度
		);

	//設定した色でバックバッファを塗りつぶす。
	SDL_RenderClear(mRenderer);

	//不透明白色の長方形をかく。
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	SDL_Rect wall{
		0, //長方形の左上隅のx(x,yはウィンドウの左上隅から右にxが増え、下にyが増えると考える。)
		0, //長方形の左上隅のy
		1024, //長方形の幅
		thickness //長方形の高さ
	};

	SDL_RenderFillRect(mRenderer, &wall);

	//下の壁追加
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//右の壁追加
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	//Paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x - thickness / 2), //これ元のは、引いてないけど、引いたほうが良さそう。
		static_cast<int>(mPaddlePos.y - paddle_H / 2),
		thickness,
		paddle_H
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	//Ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	//フロントバッファとバックバッファの入れ替えこれで描画することになる。
	SDL_RenderPresent(mRenderer);

	if (mBallPos.x < 0.0f) {
		mlsRunning = false;
	}
}