#pragma once
#include "Character.h"

struct JumpTrg
{
	// ジャンプの準備
	bool operator()(Sprite& sprite, Setting& setting);
};