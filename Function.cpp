#include "Function.h"



float Dot(const Vector3& v1, const Vector3& v2) { 
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
}

Vector3 AddVector3(const Vector3& v1, const Vector3& v2) { 
	return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector3 Multiply(const Vector3& v, float scalar) { 
	return {v.x * scalar, v.y * scalar, v.z * scalar};
}

Vector3 ToCartesian(const Spherical& s) {
	float rho = s.radius * std::cos(s.theta);
	return {rho * std::cos(s.phi), s.radius * std::sin(s.theta), rho * std::sin(s.phi)};
}

Vector3 Cross(const Vector3& v1, const Vector3& v2) { 
	Vector3 result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return result;
}

Vector3 Normalize(const Vector3& v) { 
	float length = std::sqrt(Dot(v, v)); // or std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z)

	if (length == 0.0f) {
		return {0.0f, 0.0f, 0.0f};
	}
	return Multiply(v, 1.0f / length);
}

Spherical ToSpherical(const Vector3& p) { 
	float r = std::sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	if (r == 0.0f) {
		return {0.0f, 0.0f, 0.0f};
	}
	float sinTheta = std::clamp(p.y / r, -1.0f, 1.0f);
	float phi = 0.0f;
	if (p.x != 0.0f || p.z != 0.0f) {
		phi = std::atan2(p.z, p.x);
	}

	return {r, std::asin(sinTheta), phi};
}