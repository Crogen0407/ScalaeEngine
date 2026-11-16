#pragma once

struct Vertex 
{
	Vector3D position;
	Color color;
	Vector2D uv;
};

struct TransformData
{
	Vector3D offset;
	float dummy;
};