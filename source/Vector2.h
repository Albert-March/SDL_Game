#pragma once

class Vector2 {
public:
	float x;
	float y;
	Vector2()
		:x(0.0f), y(0.0f) {}
	Vector2(float _x, float _y)
		: x(_x), y(_y) {}
	inline void Normalize()
	{
		float length = sqrt(x * x + y * y);
	}
	inline Vector2 const operator+(const Vector2& other) 
	{
		return Vector2(x + other.x, y + other.y);
	}
	inline Vector2 const operator-(const Vector2& other)
	{
		return Vector2(x - other.x, y - other.y);
	}
	inline Vector2 const operator*(const float& other)
	{
		return Vector2(x * other, y * other);
	}
};