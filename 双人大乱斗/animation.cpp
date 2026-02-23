#include"animation.h"

void Animation::reset()
{
	timer = 0;
	idx_frame = 0;
}

void Animation::set_atlas(Atlas* new_atlas)
{
	reset();
	atlas = new_atlas;
}

void Animation::set_loop(bool flag)
{
	is_loop = flag;
}

void Animation::set_interval(int ms)
{
	interval = ms;
}

int Animation::get_idx_frame()
{
	return idx_frame;
}

IMAGE* Animation::get_frame()
{
	if (!atlas) return nullptr;
	return atlas->get_image(idx_frame);
}

bool Animation::check_finished()
{
	if (is_loop)return false;
	if (!atlas) return true;
	return(idx_frame == atlas->get_size() - 1);
}

void Animation::on_update(int delta)
{
	if (!atlas) return;
	int atlas_size = atlas->get_size();
	if (atlas_size == 0) return;

	timer += delta;
	//通过累计时间判断帧索引
	while (interval > 0 && timer >= interval)
	{
		timer -= interval;
		if (is_loop)
		{
			idx_frame = (idx_frame + 1) % atlas_size;
		}
		else
		{
			if (idx_frame < atlas_size - 1)
			{
				idx_frame++;
				if (idx_frame == atlas_size - 1 && callback)
				{
					callback();
				}
			}
		}
	}

	//防止越界
	if (interval == 0)
	{
		if (idx_frame >= atlas_size) idx_frame = atlas_size - 1;
	}
}

void Animation::on_draw(const Camera& camera, int x, int y)const
{
	if (!atlas) return;
	IMAGE* img = atlas->get_image(idx_frame);
	if (!img) return;
	putimage_alpha(camera, x, y, img);
}

void Animation::set_callback(const std::function<void()> callback)
{
	this->callback = callback;
}