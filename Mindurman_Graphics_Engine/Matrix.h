#pragma once

#define math_pi 3.14159265358979323846f

#include <cmath>
#include <iostream>

//-----------Currently no library in project folder------------
// GLM stuff
//#include "vendor/glm/glm.hpp"
//#include "vendor/glm/gtc/matrix_transform.hpp"
//#include "vendor/glm/gtc/type_ptr.hpp"

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
	void operator += (const vec3& v2) {
		this->x = this->x + v2.x;
		this->y = this->y + v2.y;
		this->z = this->z + v2.z;
	}
	void operator -= (const vec3& v2) {
		this->x = this->x - v2.x;
		this->y = this->y - v2.y;
		this->z = this->z - v2.z;
	}
	vec3 getVector(const vec3& a, const vec3& b) {
		vec3 res;
		res.x = b.x - a.x;
		res.y = b.y - a.y;
		res.z = b.z - a.z;
		return res;
	}
	vec3 getCrossProduct(const vec3& a, const vec3& b) {
		vec3 res;
		res.x = a.y * b.z - a.z * b.y;
		res.y = a.z * b.x - a.x * b.z;
		res.z = a.x * b.y - a.y * b.x;
		return res;
	}
	vec3 getNormalized() {
		vec3 res;
		float vecLen = this->getLength();
		res.x = this->x / vecLen;
		res.y = this->y / vecLen;
		res.z = this->z / vecLen;
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
};