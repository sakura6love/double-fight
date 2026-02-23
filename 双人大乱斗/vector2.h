#pragma once

#include<cmath>

class Vector2
{
public:
	Vector2() = default;

	~Vector2() = default;

	Vector2(float x, float y)
		: x(x), y(y) { }

	Vector2 operator+(const Vector2& vec) const;

	void operator+=(const Vector2 & vec);

	void operator-=(const Vector2& vec);

	Vector2 operator-(const Vector2& vec) const;

	float operator*(const Vector2& vec) const;

	Vector2 operator*(float val) const;

	void operator*=(float val);

	float length();

	Vector2 normalize();

public:
	float x = 0;
	float y = 0;
};
