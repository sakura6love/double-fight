#pragma once

#include"bullet.h"
#include"animation.h"

extern IMAGE img_pea;
extern Atlas atlas_pea_break;

class PeaBullet : public Bullet
{
public:
	PeaBullet();
	~PeaBullet() = default;

	void on_collide();

	void on_update(int delta);

	void on_draw(const Camera& camera) const;

private:
	//Íã¶¹×Óµ¯ÆÆËé¶¯»­
	Animation animation_break;
};