#pragma once
#include <numbers>
#include <cmath>
#include <algorithm>

class Function {
};

const float halfPi = std::numbers::pi_v<float> / 2.0f;

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

struct Matrix4x4 {
	float m[4][4];
};

struct Segment {
	Vector3 origin;
	Vector3 diff;
};

struct Capsule {
	Segment segment;
	float radius;
};

struct Sphere {
	Vector3 center;
	float radius;
};

struct Plane {
	Vector3 normal;
	float distance;
};

struct Triangle {
	Vector3 vertices[3];
};

struct AABB {
	Vector3 min;
	Vector3 max;

	void Fix() {
		if (min.x > max.x)
			std::swap(min.x, max.x);
		if (min.y > max.y)
			std::swap(min.y, max.y);
		if (min.z > max.z)
			std::swap(min.z, max.z);
	}
};

struct Spring {
	Vector3 anchor;
	float naturalLength;
	float stiffness;
	float dampingCoefficient;
};

struct Ball {
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float mass;
	float radius;
	unsigned int color;
};

struct Pendulum {
	Vector3 anchor;
	float length;
	float angle;
	float angularVelocity;
	float angularAcceleration;
};

struct ConicalPendulum {
	Vector3 anchor;
	float length;
	float halfApexAngle;
	float angle;
	float angularVelocity;
};

float Dot(const Vector3& v1, const Vector3& v2);

Vector3 AddVector3(const Vector3& v1, const Vector3& v2);
Vector3 Multiply(const Vector3& v, float scalar);

Vector3 ToCartesian(const Spherical& s);

Vector3 Cross(const Vector3& v1, const Vector3& v2);

Vector3 Normalize(const Vector3& v);

Spherical ToSpherical(const Vector3& p);

