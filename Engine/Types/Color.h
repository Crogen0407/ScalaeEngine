#pragma once

struct Color
{
	union
	{
		struct
		{
			float r, g, b, a;
		};
		float c[4];
	};

	Color() : r(0), g(0), b(0), a(1) {}
	Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

	const float* Data() const { return c; }
	float* Data() { return c; }

	operator const float* () const { return c; }
};