#include"player.h"

Player::Player(bool facing_right) :is_facing_right(facing_right)
{
	current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;

	timer_attack_cd.set_wait_time(attack_cd);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_callback([&]()
		{
			can_attack = true;
		});

	timer_invulnerable.set_wait_time(750);
	timer_invulnerable.set_one_shot(true);
	timer_invulnerable.set_callback([&]()
		{
			is_invulnerable = false;
		});
	timer_invulnerable_blink.set_wait_time(75);
	timer_invulnerable_blink.set_callback([&]()
		{
			is_showing_sketch_frame = !is_showing_sketch_frame;
		});

	timer_run_effect_generation.set_wait_time(75);
	timer_run_effect_generation.set_callback([&]()
		{
			Vector2 particle_position;
			IMAGE* frame = atlas_run_effect.get_image(0);
			if (!frame) return;
			particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
			particle_position.y = position.y + size.y - frame->getheight();
			particle_list.emplace_back(particle_position, &atlas_run_effect, 45);
		});

	timer_die_effect_generation.set_wait_time(35);
	timer_die_effect_generation.set_callback([&]()
		{
			Vector2 particle_position;
			IMAGE* frame = atlas_run_effect.get_image(0);
			if (!frame) return;
			particle_position.x = position.x + (size.x - frame->getwidth()) / 2;
			particle_position.y = position.y + size.y - frame->getheight();
			particle_list.emplace_back(particle_position, &atlas_run_effect, 150);
		});

	animation_jump_effect.set_atlas(&atlas_jump_effect);
	animation_jump_effect.set_interval(25);
	animation_jump_effect.set_loop(false); // play once then callback
	animation_jump_effect.set_callback([&]()
		{
			is_jump_effect_visible = false;
		});

	animation_land_effect.set_atlas(&atlas_land_effect);
	animation_land_effect.set_interval(50);
	animation_land_effect.set_loop(false); // play once then callback
	animation_land_effect.set_callback([&]()
		{
			is_land_effect_visible = false;
		});

	timer_cursor_visibility.set_wait_time(2500);
	timer_cursor_visibility.set_one_shot(true);
	timer_cursor_visibility.set_callback([&]()
		{
			is_cursor_visible = false;
		});
}

void Player::set_id(PlayerID id)
{
	this->id = id;
}

void Player::on_input(const ExMessage& msg)
{
	switch (msg.message)
	{
	case WM_KEYDOWN:
		switch (id)
		{
		case PlayerID::P1:
			switch (msg.vkcode)
			{
			case 0x41://  'A'
				is_left_key_down = true;
				break;
			case 0x44://  'D'
				is_right_key_down = true;
				break;
			case 0x57://  'W'
				on_jump();
				break;
			case 0x46://  'F'
				if (can_attack)
				{
					on_attack();
					can_attack = false;
					timer_attack_cd.restart();
				}
				break;//  'G'
			case 0x47:
				if (mp >= 100)
				{
					on_attack_ex();
					mp = 0;
				}
				break;
			}
			break;
		case PlayerID::P2:
			switch (msg.vkcode)
			{
			case VK_LEFT:
				is_left_key_down = true;
				break;
			case VK_RIGHT:
				is_right_key_down = true;
				break;
			case VK_UP:
				on_jump();
				break;
			case VK_OEM_PERIOD://  '.'
				if (can_attack)
				{
					on_attack();
					can_attack = false;
					timer_attack_cd.restart();
				}
				break;
			case VK_OEM_2://  '/'
				if (mp >= 100)
				{
					on_attack_ex();
					mp = 0;
				}
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (id)
		{
		case PlayerID::P1:
			switch (msg.vkcode)
			{
			case 0x41:
				is_left_key_down = false;
				break;
			case 0x44:
				is_right_key_down = false;
				break;
			}
			break;
		case PlayerID::P2:
			switch (msg.vkcode)
			{
			case VK_LEFT:
				is_left_key_down = false;
				break;
			case VK_RIGHT:
				is_right_key_down = false;
				break;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Player::on_update(int delta)
{
	//角色图像更新
	int direction = (int)is_right_key_down - (int)is_left_key_down; // right positive
	if (direction != 0)
	{
		if(!is_attacking_ex)
			is_facing_right = direction > 0;
		current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
		float distance = direction * run_velocity * delta;
		on_run(distance);
	}
	else
	{
		current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
		timer_run_effect_generation.pause();
	}

	if (is_attacking_ex)
		current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;

	if (hp <= 0)
		current_animation = last_hurt_direction.x < 0 ? &animation_die_left : &animation_die_right;

	//动画类的更新
	if (current_animation) current_animation->on_update(delta);
	animation_jump_effect.on_update(delta);
	animation_land_effect.on_update(delta);
	//计时器类的更新
	timer_attack_cd.on_update(delta);
	timer_invulnerable.on_update(delta);
	timer_invulnerable_blink.on_update(delta);
	timer_run_effect_generation.on_update(delta);
	timer_cursor_visibility.on_update(delta);
	//死亡更新
	if (hp <= 0)
		timer_die_effect_generation.on_update(delta);
	//更新粒子
	particle_list.erase(std::remove_if(
		particle_list.begin(), particle_list.end(),
		[](const Particle& particle)
		{
			return !particle.check_valid();
		}),
		particle_list.end());
	for (Particle& particle : particle_list)
		particle.on_update(delta);
	//更新无敌闪光
	if (is_showing_sketch_frame)
	{
		IMAGE* frame = current_animation->get_frame();
		if (frame) sketch_image(frame, &img_sketch);
	}
	//移动与碰撞
	move_and_collide(delta);

	// update effect positions so they follow player
	if (is_jump_effect_visible)
	{
		IMAGE* ef = animation_jump_effect.get_frame();
		if (ef)
		{
			position_jump_effect.x = position.x + (size.x - ef->getwidth()) / 2 + jump_effect_offset_x;
			position_jump_effect.y = position.y + size.y - ef->getheight() + jump_effect_offset_y;
		}
	}
	if (is_land_effect_visible)
	{
		IMAGE* ef = animation_land_effect.get_frame();
		if (ef)
		{
			position_land_effect.x = position.x + (size.x - ef->getwidth()) / 2 + land_effect_offset_x;
			position_land_effect.y = position.y + size.y - ef->getheight() + land_effect_offset_y;
		}
	}
}

void Player::on_draw(const Camera& camera)
{
	//跳跃
	if (is_jump_effect_visible)
		animation_jump_effect.on_draw(camera, (int)position_jump_effect.x, (int)position_jump_effect.y);
	//落地
	if (is_land_effect_visible)
		animation_land_effect.on_draw(camera, (int)position_land_effect.x, (int)position_land_effect.y);
	//移动粒子
	for (const Particle& particle : particle_list)
		particle.on_draw(camera);
	//角色绘制（无敌闪光）
	if (hp > 0 && is_invulnerable && is_showing_sketch_frame)
		putimage_alpha(camera, (int)position.x, (int)position.y, &img_sketch);
	else
		if (current_animation) current_animation->on_draw(camera, (int)position.x, (int)position.y);

	if (is_cursor_visible)
	{
		switch (id)
		{
		case PlayerID::P1:
			if (&img_1P_cursor) putimage_alpha(camera, (int)(position.x + (size.x - img_1P_cursor.getwidth()) / 2),
				(int)(position.y - img_1P_cursor.getheight()), &img_1P_cursor);
			break;
		case PlayerID::P2:
			if (&img_2P_cursor) putimage_alpha(camera, (int)(position.x + (size.x - img_2P_cursor.getwidth()) / 2),
				(int)(position.y - img_2P_cursor.getheight()), &img_2P_cursor);
			break;
		}
	}

	//debug模式
	if (is_debug)
	{
		setlinecolor(RGB(0, 125, 255));
		rectangle((int)position.x, (int)position.y, (int)(position.x + size.x), (int)(position.y + size.y));
	}
}

void Player::set_position(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Player::on_run(float distance)
{
	if (is_attacking_ex)return;

	position.x += distance;
	timer_run_effect_generation.resume();
}

//物理模拟
void Player::move_and_collide(int delta)
{
	float last_velocity_y = velocity.y;

	velocity.y += gravity * delta;
	position += velocity * (float)delta;

	//角色死亡后，不进行物理判定，直接return
	if (hp < 0)
		return;

	if (velocity.y > 0)
	{
		for (const Platform& platform : platform_list)
		{
			const Platform::CollisionShape& shape = platform.shape;
			bool is_collide_x = (max(position.x + size.x, shape.right) - min(position.x, shape.left)
				<= size.x + (shape.right - shape.left));
			bool is_collide_y = (shape.y >= position.y && shape.y <= position.y + size.y);

			if (is_collide_x && is_collide_y)
			{
				float delta_pos_y = velocity.y * delta;
				float last_tick_foot_pos_y = position.y + size.y - delta_pos_y;
				if (last_tick_foot_pos_y <= shape.y)
				{
					position.y = shape.y - size.y;
					velocity.y = 0;

					if (last_velocity_y != 0)
					on_land();

					break;
				}
			}
		}
	}
	if (!is_invulnerable) {
		for (Bullet* bullet : bullet_list)
		{
			if (!bullet->get_valid() || bullet->get_collide_target() != id)
				continue;

			if (bullet->check_collision(position, size))
			{
				make_invulnerable();
				bullet->on_collide();
				bullet->set_valid(false);
				hp -= bullet->get_damage();
				//判断受击方向
				last_hurt_direction = bullet->get_position() - position;
				if (hp <= 0)
				{
					//设置死亡飞出速度
					velocity.x = last_hurt_direction.x < 0 ? 0.35f : -0.35f;
					velocity.y = -1.0f;
				}
			}
		}
	}
}

void Player::on_jump()
{
	if (velocity.y != 0 || is_attacking_ex)
		return;
	velocity.y += jump_velocity;
	is_jump_effect_visible = true;
	animation_jump_effect.reset();

	IMAGE* effect_frame = animation_jump_effect.get_frame();
	if (effect_frame)
	{
		position_jump_effect.x = position.x + (size.x - effect_frame->getwidth()) / 2;
		position_jump_effect.y = position.y + size.y - effect_frame->getheight();
		// store offsets so effect can follow player movement
		jump_effect_offset_x = position_jump_effect.x - position.x;
		jump_effect_offset_y = position_jump_effect.y - position.y;
	}
}

const Vector2& Player::get_position() const
{
	return position;
}

const Vector2& Player::get_size() const
{
	return size;
}

void Player::make_invulnerable()
{
	is_invulnerable = true;
	timer_invulnerable.restart();
	timer_invulnerable_blink.restart();
}

int Player::get_hp() const
{
	return hp;
}

int Player::get_mp() const
{
	return mp;
}

void Player::on_land()
{
	is_land_effect_visible = true;
	animation_land_effect.reset();

	IMAGE* effect_frame = animation_land_effect.get_frame();
	if (effect_frame)
	{
		position_land_effect.x = position.x + (size.x - effect_frame->getwidth()) / 2;
		position_land_effect.y = position.y + size.y - effect_frame->getheight();
		land_effect_offset_x = position_land_effect.x - position.x;
		land_effect_offset_y = position_land_effect.y - position.y;
	}
}

void Player::set_hp(int val)
{
	hp = val;
}