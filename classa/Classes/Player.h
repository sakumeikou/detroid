#pragma once
#include <tuple>
#include <array>
#include "cocos2d.h"
#include "input/Input.h"

// プレイヤーアニメーションの種類
enum class PL_ACTION
{
	IDLE,		// 立ち状態
	RIGHT_MOVE, // 右移動
	LEFT_MOVE,	// 左移動
	JUMP,		// ジャンプする直前
	JUMPING,	// ジャンプ中
	FALL,		// 落下
	RUN_SHOT,	// 走りながら弾発射
	MAX
};

class ActCtrl;

// アニメーションデータ　		 <plist,画像名,フレーム数 >
using PlayerAnimData = std::tuple<std::string, std::string, int>;

class Player :
	public cocos2d::Sprite
{
public:
	// プレイヤークラスを生成する
	static cocos2d::Sprite *createSprite();
	Player();
	~Player();
	void Init();
	void update(float delta);
	          
	// keyのトリガー情報を取得する関数
	INPUT_TRG GetInputTrg(cocos2d::EventKeyboard::KeyCode keyCode);

	// 現在実行中のアクションタイプ取得
	const PL_ACTION GetActType();
	void SetActType(PL_ACTION actType);
	const float GetJumpSpeed();
	void SetJumpSpeed(float jumpSpeed);

private:

	Input* _input;

	ActCtrl* _actCtrl;		// アクションを管理

	float _JumpSpeed;		// ジャンプのスピード

	// アニメーションの実行
	void RunAnim(PL_ACTION animType);
	std::array<std::string, static_cast<int>(PL_ACTION::MAX)> _animName; // アニメーション名

	PL_ACTION _actNow;					// 現在のアニメーション
	PL_ACTION _actOld;					// 1フレーム前のアニメーション
	
};
