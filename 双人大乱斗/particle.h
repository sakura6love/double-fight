#pragma once

#include"util.h"
#include "atlas.h"
#include "vector2.h"

//移动粒子特效
class Particle
{
public:
	Particle() = default;

	Particle(const Vector2& position, Atlas* atlas, int lifespan)
		: position(position), atlas(atlas), lifespan(lifespan){ }

	~Particle() = default;

	void set_atlas(Atlas* new_atlas);

	void set_position(const Vector2& new_position);

	void set_lifespan(int ms);

	bool check_valid() const;

	void on_update(int delta);

	void on_draw(const Camera& camera) const;

private:
	//粒子动画播放计时器
	int timer = 0;
	//单帧粒子动画持续时长
	int lifespan = 0;
	//当前动画帧
	int idx_frame = 0;

	Vector2 position;			//坐标
	bool valid = true;			//有效性
	Atlas* atlas = nullptr;		//粒子图集
};
