#include "Matrix.h"

void mat4x4::makeIdentity() {
	mat4[0][0] = 1.0f;
	mat4[1][1] = 1.0f;
	mat4[2][2] = 1.0f;
	mat4[3][3] = 1.0f;
				  
	//mat4[1][0] = 1.0f;
}

//void mat4x4::mIdentity() {
//	mat5[0] = 1;
//	mat5[5] = 1;
//	mat5[10] = 1;
//	mat5[15] = 1;
//}

void mat4x4::makePerspective(float near, float far, float fov, float aspectRatio) //Aspect ratio = Height/Width
{
	float left = near * tanf(fov / 2); float right = -left;
	float top = left * aspectRatio; float bottom = -top;

	mat4[0][0] = 2 * near / (right - left);
	mat4[2][0] = (right + left) / (right - left);
	mat4[1][1] = 2 * near / (top - bottom);
	mat4[2][1] = (top + bottom) / (top - bottom);
	mat4[2][2] = (-far - near) / (far - near);
	mat4[3][2] = -2 * far * near / (far - near);
	mat4[2][3] = -1.0f;
}

void mat4x4::makeView(const vec3& eye, const vec3& target, const vec3& up) {
	vec3 forward; 
	//forward = forward.getVector(target, eye); //original
	forward = forward.getVector(eye, target);
	forward.normalize();
	/*forward.x = -forward.x; forward.y = -forward.y; forward.z = -forward.z;*/

	vec3 left;
	//left = left.getCrossProduct(up, forward); //original
	//left.normalize();
	left = left.getCrossProduct(forward, up); 
	left.normalize();
	left.x = -left.x; left.y = -left.y; left.z = -left.z;

	vec3 upvec;
	upvec = upvec.getCrossProduct(forward, left); 

	//negate direction vector 
	forward.x = -forward.x; forward.y = -forward.y; forward.z = -forward.z;

	mat4[0][0] = left.x;
	mat4[1][0] = left.y;
	mat4[2][0] = left.z;
	mat4[3][0] = -(left.dotProduct(left, eye)); 

	mat4[0][1] = upvec.x;
	mat4[1][1] = upvec.y;
	mat4[2][1] = upvec.z;
	mat4[3][1] = -(upvec.dotProduct(upvec, eye)); 

	mat4[0][2] = forward.x;
	mat4[1][2] = forward.y;
	mat4[2][2] = forward.z;
	mat4[3][2] = -(forward.dotProduct(forward, eye));

	mat4[3][3] = 1.0f;
}

void mat4x4::makeTranslation(float x, float y, float z) {
	mat4[0][0] = 1.0f;
	mat4[1][1] = 1.0f;
	mat4[2][2] = 1.0f;
	mat4[3][3] = 1.0f;

	mat4[3][0] = x;
	mat4[3][1] = y;
	mat4[3][2] = z;
}