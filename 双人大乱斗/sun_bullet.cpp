#include"sun_bullet.h"

SunBullet::SunBullet()
{
	size.x = 96;
	size.y = 96;
	damage = 20;

	animation_idle.set_atlas(&atlas_sun);
	animation_idle.set_interval(50);

	animation_explode.set_atlas(&atlas_sun_explode);
	animation_explode.set_interval(50);
	animation_explode.set_loop(false);
	animation_explode.set_callback([&]() {can_remove = true; });

	IMAGE* frame_idle = animation_idle.get_frame();
	IMAGE* frame_explode = animation_explode.get_frame();
	explode_render_offset.x = (frame_idle->getwidth() - frame_explode->getwidth()) / 2.0f;
	explode_render_offset.y = (frame_idle->getheight() - frame_explode->getheight()) / 2.0f;
}

void SunBullet::on_collide()
{
	Bullet::on_collide();

	main_camera.shake(5, 250);

	mciSendString(_T("play sun_explode from 0"), NULL, 0, NULL);
}

void SunBullet::on_update(int delta)
{
	//判断速度
	if (valid) 
	{
		velocity.y += gravity * delta;
		position += velocity * (float)delta;
	}
	//判断动画更新
	if(!valid)
	{
		animation_explode.on_update(delta);
	}
	else
	{
		animation_idle.on_update(delta);
	}

	if (check_if_exceed_screen())
	{
		can_remove = true;
	}
}

void SunBullet::on_draw(const Camera& camera) const
{
	if (valid)
	{
		animation_idle.on_draw(camera, (int)position.x, (int)position.y);
	}
	else 
	{
		animation_explode.on_draw(camera,
			(int)(position.x + explode_render_offset.x),
			(int)(position.y + explode_render_offset.y));
	}
	Bullet::on_draw(camera);
}