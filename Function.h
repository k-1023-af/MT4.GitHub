#pragma once
#include <numbers>
#include <cmath>
#include <algorithm>

class Function {
};


struct Vector3 {
	float x;
	float y;
	float z;

	// constructor
	Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

	// Put Compound Assignment Operators inside the class
	Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
	Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return *this; }
};

struct Spherical {
	float radius;
	float theta;
	float phi;
};

Vector3 ToCartesian(const Spherical& s);
Spherical ToSpherical(const Vector3& p);