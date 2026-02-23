#pragma once

#include<graphics.h>

#include"camera.h"

class Scene 
{
public:
	Scene() = default;

	~Scene() = default;

	//进入场景
	virtual void on_enter(){ }
	//处理数据
	virtual void on_update(int delta){ }
	//渲染绘图
	virtual void on_draw(const Camera& camera){ }
	//处理输入
	virtual void on_input(const ExMessage& msg){ }
	//退出场景
	virtual void on_exit(){ }

private:

};