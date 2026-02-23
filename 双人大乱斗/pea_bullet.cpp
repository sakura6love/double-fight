#include"pea_bullet.h"

PeaBullet::PeaBullet()
{
	size.x = 64;
	size.y = 64;
	damage = 10;

	animation_break.set_atlas(&atlas_pea_break);
	animation_break.set_interval(100);
	animation_break.set_loop(false);
	//通过回调函数，使子弹在破碎动画播放后会被移除
	animation_break.set_callback([&]() {can_remove = true; });
}

void PeaBullet::on_collide()
{
	Bullet::on_collide();

	//随机播放豌豆破碎音效
	switch (rand() % 3)
	{
	case 0:
		mciSendString(_T("play pea_break_1 from 0"), NULL, 0, NULL);
		break;
	case 1:
		mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
		break;
	case 2:
		mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
		break;
	}
}

void PeaBullet::on_update(int delta)
{
	position += velocity * (float)delta;
	//子弹破碎更新动画
	if (!valid)
	{
		animation_break.on_update(delta);
	}
	//判断子弹飞出
	if (check_if_exceed_screen())
	{
		can_remove = true;
	}
}

void PeaBullet::on_draw(const Camera& camera) const
{
	if (valid)
	{
		putimage_alpha(camera, (int)position.x, (int)position.y, &img_pea);
	}
	else
	{
		animation_break.on_draw(camera, (int)position.x, (int)position.y);
	}
	Bullet::on_draw(camera);
}