#pragma once

#include"camera.h"
#include"bullet.h"
#include"vector2.h"
#include"platform.h"
#include"particle.h"
#include"animation.h"
#include"player_id.h"

#include<graphics.h>

extern bool is_debug;

extern std::vector<Bullet*> bullet_list;
extern std::vector<Platform> platform_list;
//角色头顶光标
extern IMAGE img_1P_cursor;
extern IMAGE img_2P_cursor;
//粒子特效图集
extern Atlas atlas_run_effect;
extern Atlas atlas_jump_effect;
extern Atlas atlas_land_effect;

class Player
{
public:
	Player(bool facing_right = true);

	~Player() = default;

	virtual void on_update(int delta);

	virtual void on_draw(const Camera& camera);

	virtual void on_input(const ExMessage& msg);

	void set_id(PlayerID id);

	void set_position(float x, float y);

	virtual void on_run(float ditance);

	virtual void on_jump();

	virtual void on_land();

	virtual void on_attack() { };

	virtual void on_attack_ex() { };

	const Vector2& get_position() const;

	const Vector2& get_size() const;

	void make_invulnerable();

	int get_hp() const;

	int get_mp() const;

	void set_hp(int val);

protected:
	void move_and_collide(int delta);

protected:
	//角色能量
	int mp = 0;
	//角色血量
	int hp = 100;

	//角色尺寸
	Vector2 size;
	//角色位置
	Vector2 position;
	//角色速度
	Vector2 velocity;

	//角色静止、移动动画
	Animation animation_idle_left;
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_attack_ex_left;
	Animation animation_attack_ex_right;
	Animation animation_jump_effect;
	Animation animation_land_effect;
	Animation animation_die_left;
	Animation animation_die_right;

	//动画特效是否可见
	bool is_jump_effect_visible = false;
	bool is_land_effect_visible = false;
	//特效动画播放位置
	Vector2 position_jump_effect;
	Vector2 position_land_effect;
	// offsets so effects follow player
	float jump_effect_offset_x = 0.0f;
	float jump_effect_offset_y = 0.0f;
	float land_effect_offset_x = 0.0f;
	float land_effect_offset_y = 0.0f;

	//当前动画指针
	Animation* current_animation = nullptr;
	//玩家序号ID
	PlayerID id = PlayerID::P1;
	//判断移动按键
	bool is_left_key_down = false;
	bool is_right_key_down = false;
	//判断角色朝向
	bool is_facing_right = true;

	//冷却时间
	int attack_cd = 500;
	//是否可以释放攻击
	bool can_attack = true;
	//攻击冷却计时器
	Timer timer_attack_cd;

	//是否正在释放特殊攻击
	bool is_attacking_ex = false;

	//动画帧剪影图片
	IMAGE img_sketch;

	//角色是否处于无敌状态
	bool is_invulnerable = false;
	//当前帧是否应该显示剪影
	bool is_showing_sketch_frame = false;

	//无敌状态定时器，无敌状态闪烁定时器
	Timer timer_invulnerable;
	Timer timer_invulnerable_blink;

	//粒子对象列表
	std::vector<Particle> particle_list;

	//跑动、死亡特效粒子发射定时器（粒子发射器）
	Timer timer_run_effect_generation;
	Timer timer_die_effect_generation;

	bool is_cursor_visible = true;
	Timer timer_cursor_visibility;

	//最后一次受击方向
	Vector2 last_hurt_direction;

protected:
	//玩家重力
	const float gravity = 1.6e-3f;
	//跑动速度
	const float run_velocity = 0.55f;
	//跳跃速度
	const float jump_velocity = -0.85f;
};
