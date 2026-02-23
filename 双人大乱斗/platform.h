#pragma once

#include"util.h"
#include"camera.h"

extern bool is_debug;

class Platform
{
public:
	Platform() = default;

	~Platform() = default;

	void on_draw(const Camera& camera) const;

public:
	struct CollisionShape
	{
		float y;
		float left, right;
	};

public:
	CollisionShape shape;
	IMAGE* img = nullptr;
	POINT render_position = { 0 };
};
