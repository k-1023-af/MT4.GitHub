#include "Function.h"



float Dot(const Vector3& v1, const Vector3& v2) { 
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; 
}

float Vector2Length(Vector2 v1, Vector2 v2) { 
	return sqrtf(powf(((float)v2.x - (float)v1.x), 2) + powf(((float)v2.y - (float)v1.y), 2));
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

Quaternion MultiplyQuaternion(const Quaternion& lhs, const Quaternion& rhs) { 
	Quaternion result; 
	result.w = (lhs.w * rhs.w) - (lhs.x * rhs.x) - (lhs.y * rhs.y) - (lhs.z * rhs.z);
	result.x = (lhs.y * rhs.z) - (lhs.z * rhs.y) + (rhs.w * lhs.x) + (lhs.w * rhs.x);
	result.y = (lhs.z * rhs.x) - (lhs.x * rhs.z) + (rhs.w * lhs.y) + (lhs.w * rhs.y);
	result.z = (lhs.x * rhs.y) - (lhs.y * rhs.x) + (rhs.w * lhs.z) + (lhs.w * rhs.z);
	return result;
}

Quaternion IdentityQuaternion() { 
	Quaternion result;
	result.w = 1.0f;
	result.x = 0.0f;
	result.y = 0.0f;
	result.z = 0.0f;
	return result;
}

Quaternion Conjugate(const Quaternion& q) { 
	Quaternion result;	//q*
	result.w = q.w;
	result.x = -1 * q.x;
	result.y = -1 * q.y;
	result.z = -1 * q.z;
	return result;
}

float Norm(const Quaternion& q) { 
	float absValue = sqrtf(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);

	return absValue;
}

Quaternion Normalize(const Quaternion& q) { 
	float norm = Norm(q);
	if (norm < 0.001f) {
		return {1.0f, 0.0f, 0.0f, 0.0f};
	}

	float inverse = 1.0f / norm;

	Quaternion result = q;
	result.w *= inverse;
	result.x *= inverse;
	result.y *= inverse;
	result.z *= inverse;
	return result;
}

Quaternion Inverse(const Quaternion& q) { 
	Quaternion result;
	float normSq = (q.w * q.w) + (q.x * q.x) + (q.y * q.y) + (q.z * q.z);
	if (normSq < 0.001f) {
		return result = {1.0f, 0.0f, 0.0f, 0.0f};
	}

	float inverseNormSq = 1.0f / normSq;

	Quaternion conj = Conjugate(q);

	result.w = conj.w * inverseNormSq;
	result.x = conj.x * inverseNormSq;
	result.y = conj.y * inverseNormSq;
	result.z = conj.z * inverseNormSq;
	return result;
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