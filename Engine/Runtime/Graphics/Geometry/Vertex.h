#pragma once

struct Vertex 
{
	Vector3D position;
	Color color;
	Vector2D uv;
};

struct TransformData
{
	Matrix4x4 matWorld = Matrix4x4::Identity;
	Matrix4x4 matView = Matrix4x4::Identity;
	Matrix4x4 matProjection = Matrix4x4::Identity;
};