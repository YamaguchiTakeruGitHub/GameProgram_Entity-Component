#pragma once
#include "../../../Library/TakeruLib.h"

/// <summary>
/// 基本コンポーネント
/// </summary>
class Component
{
public:
	virtual ~Component() = default;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Final() = 0;

};

