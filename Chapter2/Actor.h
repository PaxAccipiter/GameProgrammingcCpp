#pragma once
#include "Game.h"
#include "Math.h"
#include <vector>

class Actor {
public:
	//Actorの状態管理
	enum State {
		EActive,
		EPaused,
		EDead
	};

	//コンストラクタとデストラクター
	Actor(class Game* game);
	virtual ~Actor();

	//gameから呼び出される更新関数(オーバーライド不可)
	void Update(float deltaTime);
	//Actorの持つ全コンポーネントを更新(オーバーライド不可)
	void UpdateComponents(float deltaTime);
	//Actor独自の更新処理(オーバーライド可能)
	virtual void UpdateActor(float deltaTime);

	//ゲッター、セッター(メンバの値の取得と設定)

	//コンポーネントの追加と削除
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	//アクターの状態
	State mState;
	
	//座標変換
	Vector2 mPosition; //アクターの中心位置
	float mScale; //アクターのスケール(1.0fが100%)
	float mRotation; //回転の角度(ラジアン)

	//アクターが持つコンポーネント
	std::vector<class Component*> mComponents;
	class Game* mGame;
};