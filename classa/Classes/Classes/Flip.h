#pragma once
#include "Character.h"

struct Flip
{
	// キャラの画像を逆にする処理
	bool operator()(Sprite& sprite, Setting& setting);
};