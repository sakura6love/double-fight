#include"particle.h"

void Particle::set_atlas(Atlas* new_atlas)
{
	atlas = new_atlas;
}

void Particle::set_position(const Vector2& new_position)
{
	position = new_position;
}

void Particle::set_lifespan(int ms)
{
	lifespan = ms;
}

bool Particle::check_valid() const
{
	return valid;
}

void Particle::on_update(int delta)
{
	// Validate atlas
	if (!atlas)
	{
		valid = false;
		return;
	}
	int atlas_size = atlas->get_size();
	if (atlas_size <= 0)
	{
		valid = false;
		return;
	}

	// Determine per-frame duration (evenly split lifespan among frames)
	int per_frame = lifespan > 0 ? (lifespan / atlas_size) : 0;

	if (per_frame <= 0)
	{
		// If no timing provided, advance one frame per update and expire when past last
		idx_frame++;
		if (idx_frame >= atlas_size)
		{
			idx_frame = atlas_size - 1;
			valid = false;
		}
		return;
	}

	timer += delta;
	while (timer >= per_frame && valid)
	{
		timer -= per_frame;
		idx_frame++;
		if (idx_frame >= atlas_size)
		{
			idx_frame = atlas_size - 1;
			valid = false;
			break;
		}
	}
}

void Particle::on_draw(const Camera& camera) const
{
	if (!atlas) return;
	int atlas_size = atlas->get_size();
	if (atlas_size <= 0) return;
	int frame_idx = idx_frame;
	if (frame_idx < 0) frame_idx = 0;
	if (frame_idx >= atlas_size) frame_idx = atlas_size - 1;
	IMAGE* img = atlas->get_image(frame_idx);
	if (!img) return;
	putimage_alpha(camera, (int)position.x, (int)position.y, img);
}