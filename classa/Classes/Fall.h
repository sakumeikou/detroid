#pragma once
#include "Character.h"

struct Fall
{
	// キャラを落ちていく処理
	bool operator()(Sprite& sprite, Setting& setting);
};