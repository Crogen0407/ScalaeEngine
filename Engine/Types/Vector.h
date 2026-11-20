#pragma once

struct Vector2D
{
	float x, y;

	bool operator== (const Vector2D& other) const
	{
		return x == other.x && y == other.y;
	}
	Vector2D& operator+= (const Vector2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2D& operator-= (const Vector2D& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	float& operator[](int index)
	{
		if (0 == index)
			return x;
		else
			return y;
	}
};

struct Vector3D
{
	float x, y, z;

	bool operator== (const Vector3D& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
	Vector3D& operator+= (const Vector3D& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vector3D& operator-= (const Vector3D& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vector3D& operator+= (const Vector2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector3D& operator-= (const Vector2D& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	float& operator[](int index)
	{
		if (0 == index)
			return x;
		else if (1 == index)
			return y;
		else
			return z;
	}
};

static const Vector3D Zero = { 0.f, 0.f , 0.f };
static const Vector3D One = { 1.f, 1.f , 1.f };