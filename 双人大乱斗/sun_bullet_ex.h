#pragma once

#include"bullet.h"
#include"animation.h"

extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;

extern Camera main_camera;

class SunBulletEx : public Bullet
{
public:
	SunBulletEx();
	~SunBulletEx() = default;

	void on_collide();

	void on_update(int delta);

	void on_draw(const Camera& camera) const;

	bool check_collision(const Vector2& position, const Vector2& size);

private:
	//¾Þ´ó×Óµ¯Ä¬ÈÏ¶¯»­
	Animation animation_idle;
	//¾Þ´ó×Óµ¯±¬Õ¨¶¯»­
	Animation animation_explode;
	//±¬Õ¨¶¯»­äÖÈ¾Æ«ÒÆ
	Vector2 explode_render_offset;
};