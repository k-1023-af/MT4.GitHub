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

Vector3 Transform(const Vector3& v, const Matrix4x4& m) { 
	Vector3 result;
	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + 1.0f * m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + 1.0f * m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + 1.0f * m.m[3][2];

	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + 1.0f * m.m[3][3];
	// assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion) { 
	Quaternion r = {vector.x, vector.y, vector.z, 0.0f};

	Quaternion invQ = Inverse(quaternion);

	Quaternion rotateVector = Multiply(quaternion, Multiply(r, invQ));

	Quaternion invRotate = Inverse(rotateVector);

	return {rotateVector.x, rotateVector.y, rotateVector.z};
}

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs) { 
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
		return {0.0f, 0.0f, 0.0f, 1.0f};	// { x, y, z, w }
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
		return result = {0.0f, 0.0f, 0.0f, 1.0f};	// { x, y, z, w }
	}

	float inverseNormSq = 1.0f / normSq;

	Quaternion conj = Conjugate(q);

	result.w = conj.w * inverseNormSq;
	result.x = conj.x * inverseNormSq;
	result.y = conj.y * inverseNormSq;
	result.z = conj.z * inverseNormSq;
	return result;
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle) { 
	Vector3 n = Normalize(axis); 
	float halfAngle = angle * 0.5f;
	float s = std::sin(halfAngle);

	Quaternion result;
	result.x = n.x * s;
	result.y = n.y * s;
	result.z = n.z * s;
	result.w = std::cos(halfAngle);
	return result;
}

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion) { 
	float w = quaternion.w;
	float x = quaternion.x;
	float y = quaternion.y;
	float z = quaternion.z;

	Matrix4x4 result = {};

	result.m[0][0] = (w * w) + (x * x) - (y * y) - (z * z);
	result.m[0][1] = 2 * ((x * y) + (w * z));
	result.m[0][2] =  2 * ((x * z) - (w * y));
	//result.m[0][3] = 0;

	result.m[1][0] = 2 * ((x * y) - (w * z));
	result.m[1][1] = (w * w) - (x * x) + (y * y) - (z * z);
	result.m[1][2] = 2 * ((y * z) + (w * x));
	//result.m[1][3] = 0;

	result.m[2][0] = 2 * ((x * z) + (w * y));
	result.m[2][1] = 2 * ((y * z) - (w * x));
	result.m[2][2] = (w * w) - (x * x) - (y * y) + ( z * z);
	//result.m[2][3] = 0;

	//result.m[3][0] = 0;
	//result.m[3][0] = 0;
	//result.m[3][0] = 0;
	result.m[3][3] = 1;

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

void MatrixScreenPrintf(int x, int y, Matrix4x4 matrix) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.03f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, Vector3 vector) { 
	Novice::ScreenPrintf(x + 0 * kColumnWidth, y, "%6.02f", vector.x);
	Novice::ScreenPrintf(x + 1 * kColumnWidth, y, "%6.02f", vector.y);
	Novice::ScreenPrintf(x + 2 * kColumnWidth, y, "%6.02f", vector.z);
}

void QuaternionScreenPrintf(int x, int y, Quaternion quaternion) { 
	Novice::ScreenPrintf(x + 0 * kColumnWidth, y, "%6.02f", quaternion.x); 
	Novice::ScreenPrintf(x + 1 * kColumnWidth, y, "%6.02f", quaternion.y);
	Novice::ScreenPrintf(x + 2 * kColumnWidth, y, "%6.02f", quaternion.z);
	Novice::ScreenPrintf(x + 3 * kColumnWidth, y, "%6.02f", quaternion.w);
}
