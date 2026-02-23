#include"bullet.h"

void Bullet::set_damage(int val)
{
	damage = val;
}

int Bullet::get_damage()
{
	return damage;
}

void Bullet::set_position(float x, float y)
{
	position.x = x;
	position.y = y;
}

const Vector2& Bullet::get_position()
{
	return position;
}

const Vector2& Bullet::get_size() const
{
	return size;
}

void Bullet::set_velocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Bullet::set_collide_target(PlayerID target)
{
	target_id = target;
}

PlayerID Bullet::get_collide_target() const
{
	return target_id;
}

void Bullet::set_callback(std::function<void()> callback)
{
	this->callback = callback;
}

void Bullet::set_valid(bool flag)
{
	valid = flag;
}

bool Bullet::get_valid() const
{
	return valid;
}

bool Bullet::check_can_remove() const
{
	return can_remove;
}

void Bullet::on_collide()
{
	if (callback)
	{
		callback();
	}
}

bool Bullet::check_collision(const Vector2& position, const Vector2& size)
{
	return this->position.x + this->size.x / 2 >= position.x
		&& this->position.x + this->size.x / 2 <= position.x + size.x
		&& this->position.y + this->size.y / 2 >= position.y
		&& this->position.y + this->size.y / 2 <= position.y + size.y;
}

bool Bullet::check_if_exceed_screen()
{
	return (position.x + size.x <= 0 || position.x >= getwidth()|| position.y >= getheight());
}

void Bullet::on_draw(const Camera& camera)const
{
	if (is_debug)
	{
		setfillcolor(RGB(255, 255, 255));
		setlinecolor(RGB(255, 255, 255));
		rectangle((int)position.x, (int)position.y, (int)(position.x + size.x), (int)(position.y + size.y));
		solidcircle((int)(position.x + size.x / 2), (int)(position.y + size.y / 2), 5);
	}
}