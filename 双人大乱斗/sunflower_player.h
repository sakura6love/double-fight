#pragma once

#include"player.h"
#include"sun_bullet.h"
#include"sun_bullet_ex.h"

extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;
extern Atlas atlas_sunflower_attack_ex_left;
extern Atlas atlas_sunflower_attack_ex_right;
extern Atlas atlas_sun_text;
extern Atlas atlas_sunflower_die_left;
extern Atlas atlas_sunflower_die_right;

extern Player* player_1;
extern Player* player_2;

class SunflowerPlayer : public Player
{
public:
	SunflowerPlayer(bool facing_right = true);

	~SunflowerPlayer() = default;

	void on_update(int delta);

	void on_draw(const Camera& camera);

	void on_attack();

	void on_attack_ex();

private:
	//头顶文本动画
	Animation animation_sun_text;
	//是否显示头顶文本
	bool is_sun_text_visible = false;

	const float speed_sun_ex = 0.15f;//大速度
	const Vector2& velocity_sun = { 0.25f, -0.5f };//小速度
};
