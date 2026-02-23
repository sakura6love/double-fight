#pragma once

#include"vector2.h"
#include"camera.h"
#include"player_id.h"

#include<graphics.h>
#include<functional>

extern bool is_debug;

class Bullet
{
public:
	Bullet() = default;
	~Bullet() = default;

	void set_damage(int val);

	int get_damage();

	void set_position(float x, float y);

	const Vector2& get_position();

	const Vector2& get_size() const;

	void set_velocity(float x, float y);

	void set_collide_target(PlayerID target);

	PlayerID get_collide_target() const;

	void set_callback(std::function<void()> callback);

	void set_valid(bool flag);

	bool get_valid() const;

	bool check_can_remove() const;

	virtual void on_collide();

	virtual bool check_collision(const Vector2& position, const Vector2& size);

	virtual void on_update(int ddelta) { };

	virtual void on_draw(const Camera& camera)const;

protected:
	//子弹尺寸
	Vector2 size;
	//子弹位置
	Vector2 position;
	//子弹速度
	Vector2 velocity;
	//子弹伤害
	int damage = 10;
	//子弹是否有效
	bool valid = true;
	//子弹是否可以被移除
	bool can_remove = false;
	//子弹碰撞回调函数
	std::function<void()> callback;
	//子弹碰撞目标玩家ID
	PlayerID target_id = PlayerID::P1;

protected:
	virtual bool check_if_exceed_screen();
};
