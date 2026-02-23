#pragma once

#include"timer.h"
#include"vector2.h"

class Camera
{
public:
	Camera();

	~Camera() = default;

	const Vector2& get_position() const;

	void reset();

	void on_update(int delta);

	void shake(float strength, int duration);

private:
	Vector2 position;				//摄像机位置
	Timer timer_shake;				//摄像机抖动定时器
	bool is_shaking = false;		//摄像机是否正在1抖动
	float shaking_strength = 0;		//摄像机抖动幅度
};
