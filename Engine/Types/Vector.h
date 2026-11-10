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
};