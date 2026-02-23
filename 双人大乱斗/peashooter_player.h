#pragma once

#include"player.h"
#include"pea_bullet.h"

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_attack_ex_left;
extern Atlas atlas_peashooter_attack_ex_right;
extern Atlas atlas_peashooter_die_left;
extern Atlas atlas_peashooter_die_right;

extern Camera main_camera;

class PeashooterPlayer : public Player
{
public:
	PeashooterPlayer(bool facing_right = true);

	~PeashooterPlayer() = default;

	void on_update(int delta);

	void on_attack();

	void on_attack_ex();

private:
	void spawn_pea_bullet(float speed);

private:
	const float speed_rea = 0.75f;
	const float speed_pea_ex = 1.5f;
	//特殊攻击状态持续时间
	const int attack_ex_duration = 2500;

	//特殊攻击状态定时器
	Timer timer_attack_ex;
	//豌豆子弹发射状态定时器
	Timer timer_spwan_pea_ex;
};
