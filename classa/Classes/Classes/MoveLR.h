#pragma once
#include "Character.h"

struct MoveLR
{
	// 左右移動の処理
	bool operator()(Sprite& sprite, Setting& setting);
};