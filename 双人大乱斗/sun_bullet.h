#pragma once

#include"bullet.h"
#include"animation.h"

extern Atlas atlas_sun;
extern Atlas atlas_sun_explode;

extern Camera main_camera;

class SunBullet : public Bullet
{
public:
	SunBullet();
	~SunBullet() = default;

	void on_collide();

	void on_update(int delta);

	void on_draw(const Camera& camera) const;

private:
	//×Óµ¯Ä¬ÈÏ¶¯»­
	Animation animation_idle;
	//×Óµ¯±¬Õ¨¶¯»­
	Animation animation_explode;
	//±¬Õ¨¶¯»­äÖÈ¾Æ«ÒÆ
	Vector2 explode_render_offset;

private:
	const float gravity = 1e-3f;
};