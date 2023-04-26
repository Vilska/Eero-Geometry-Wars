#pragma once

#include <math.h>
#include <random>

namespace Eero {

	class Vec2
	{
	public:
		float x, y = 0.0f;

		Vec2() = default;

		Vec2(float xin, float yin)
			: x(xin), y(yin) {}

		bool operator == (const Vec2& v2)    const { return (x == v2.x) && (y == v2.y); }
		bool operator != (const Vec2& v2)    const { return (x != v2.x) && (y != v2.y); }
										     
		Vec2 operator + (const Vec2& v2)     const { return Vec2(x + v2.x, y + v2.y); }
		Vec2 operator - (const Vec2& v2)     const { return Vec2(x - v2.x, y - v2.y); }
		Vec2 operator / (const float val)    const { return Vec2(x / val, y / val); }
		Vec2 operator * (const float val)    const { return Vec2(x * val, y * val); }
										     
		void operator += (const Vec2& v2)    { x += v2.x; y += v2.y; }
		void operator -= (const Vec2& v2)    { x -= v2.x; y -= v2.y; }
		void operator *= (const float val)   { x *= val; y *= val; }
		void operator /= (const float val)   { x /= val; y /= val; }

		float dist(const Vec2& v2)
		{
			return sqrtf((v2.x - x) * (v2.x - x) + (v2.y - y) * (v2.y - y));
		}

		float length()
		{
			return sqrtf((x * x) + (y * y));
		}
	};

	class Vec3
	{
	public:
		float x, y, z = 0.0f;

		Vec3() = default;
		Vec3(float xin, float yin, float zin)
			: x(xin), y(yin), z(zin) {}

		bool operator == (const Vec3& v2) const { return (x == v2.x) && (y == v2.y) && (z == v2.z); }
		bool operator != (const Vec3& v2) const { return (x != v2.x) && (y != v2.y) && (z != v2.z); }

		Vec3 operator + (const Vec3& v2) const { return Vec3(x + v2.x, y + v2.y, z + v2.z); }
		Vec3 operator - (const Vec3& v2) const { return Vec3(x - v2.x, y - v2.y, z - v2.z); }
		Vec3 operator / (const float val) const { return Vec3(x / val, y / val, z / val); }
		Vec3 operator * (const float val) const { return Vec3(x * val, y * val, z * val); }

		void operator += (const Vec3& v2) { x += v2.x; y += v2.y;z += v2.z; }
		void operator -= (const Vec3& v2) { x -= v2.x; y -= v2.y;z -= v2.z; }
		void operator /= (const float val) { x / val; y / val; z / val; }
		void operator *= (const float val) { x * val; y * val; z * val; } 
	};

	class Random
	{
	public:
		Random() = default;

		static int Calculate(int max, int min) 
		{
			std::random_device rd;     // Only used once to initialise seed
			std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
			std::uniform_int_distribution<int> uni(min, max); // Guaranteed unbiased

			return uni(rng);
		}
	};

}
