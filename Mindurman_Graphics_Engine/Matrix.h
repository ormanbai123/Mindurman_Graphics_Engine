#pragma once

#include <cmath>
#include <iostream>

struct vec2 {
	float u = 0.0f; 
	float v = 0.0f;
	vec2() {

	}
	vec2(float x, float y) {
		this->u = x;
		this->v = y;
	}
};

struct vec3 {
	float x = 0.0f; float y = 0.0f; float z = 0.0f;
	vec3() {

	}
	vec3(float xv, float yv, float zv) {
		this->x = xv;
		this->y = yv;
		this->z = zv;
	}
	vec3 operator+ (const vec3& v2) {
		vec3 res;
		res.x = this->x + v2.x;
		res.y = this->y + v2.y;
		res.z = this->z + v2.z;
		return res;
	}
	vec3 operator- (const vec3& v2) {
		vec3 res;
		res.x = this->x - v2.x;
		res.y = this->y - v2.y;
		res.z = this->z - v2.z;
		return res;
	}
	vec3 getVector(const vec3& vec1, const vec3& vec2) {
		vec3 res;
		res.x = vec2.x - vec1.x;
		res.y = vec2.y - vec1.y;
		res.z = vec2.z - vec1.z;
		return res;
	}
	vec3 getCrossProduct(const vec3& vec1, const vec3& vec2) {
		vec3 res;
		res.x = vec1.y * vec2.z - vec1.z * vec2.y;
		res.y = vec1.z * vec2.x - vec1.x * vec2.z;
		res.z = vec1.x * vec2.y - vec2.y * vec2.x;
		return res;
	}
	float dotProduct(const vec3& v1, const vec3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}
	float getLength() {
		return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	}
	void normalize() {
		float vecLen = this->getLength();
		this->x /= vecLen;
		this->y /= vecLen;
		this->z /= vecLen;
	}
};

class mat4x4 {
public:
	float mat4[4][4] = { 0 };
	void makeIdentity();
	void makePerspective(float n, float f, float fov, float aspectRatio);
	void makeView(const vec3& eye, const vec3& target, const vec3& up);
	void makeTranslation(float x, float y, float z);
	//float mat5[16] = { 0 };
	//void mIdentity();
};