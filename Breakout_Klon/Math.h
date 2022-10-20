#pragma once

#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f

struct Vector2 {
	float x, y;

	Vector2(float _x = 0.0f, float _y = 0.0f) {
		x = _x;
		y = _y;
	}

	float MagnitudeSqr() {
		return x * x + y * y;
	}

	float Magnitude() {
		return float(sqrt(x * x + y * y));
	}

	Vector2 Normalized() {

		float mag = Magnitude();

		return Vector2(x / mag, y / mag);

	}

	Vector2& operator += (const Vector2& rightside) {

		x += rightside.x;
		y += rightside.y;

		return *this;
	}

	Vector2& operator -= (const Vector2& leftside) {

		x -= leftside.x;
		y -= leftside.y;

		return *this;
	}

};

inline Vector2 operator +(const Vector2& leftside, const Vector2& rightside) {
	return Vector2(leftside.x + rightside.x, leftside.y + rightside.y);
}

inline Vector2 operator -(const Vector2& leftside, const Vector2& rightside) {
	return Vector2(leftside.x - rightside.x, leftside.y - rightside.y);
}

inline Vector2 operator *(const Vector2& leftside, const float& rightside) {
	return Vector2(leftside.x * rightside, leftside.y * rightside);
}

inline Vector2 operator *(const float& leftside, const Vector2& rightside) {
	return Vector2(leftside * rightside.x, leftside * rightside.y);
}

inline Vector2 operator /(const Vector2& leftside, const float& rightside) {
	return Vector2(leftside.x / rightside, leftside.y / rightside);
}

inline Vector2 operator /(const float& leftside, const Vector2& rightside) {
	return Vector2(leftside / rightside.x, leftside / rightside.y);
}
inline Vector2 RotateVector(const Vector2& vec, float angle) {
	
	float radAngle = (float)(angle * DEG_TO_RAD);

	return Vector2((float)(vec.x * cos(radAngle) - vec.y * sin(radAngle)), (float)(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

const Vector2 zeroV2 = { 0.0f, 0.0f };
const Vector2 oneV2 = {1.0f,1.0f};