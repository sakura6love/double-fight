#pragma once

#include "util.h"

class StatusBar
{
public:
	StatusBar() = default;
	~StatusBar() = default;

	void set_avatar(IMAGE* img);

	void set_position(int x, int y);

	void set_hp(int val);

	void set_mp(int val);

	void on_draw();

private:
	//需要显示的信息与位置
	int hp = 0;
	int mp = 0;
	POINT position = { 0 };
	//角色头像图片
	IMAGE* img_avatar = nullptr;
	//状态条变量
	const int width = 275;
};