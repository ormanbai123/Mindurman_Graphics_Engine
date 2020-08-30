#include "Camera.h"

Camera::Camera(const vec3& cam_pos, const vec3& cam_dir,const vec2& win_centre)
{
	this->vPos = cam_pos;
	this->vDir = cam_dir;
	this->vUp = vec3(0.0f, 1.0f, 0.0f);

	m_last_pos = win_centre;
}

void Camera::input_mouse(double winPos_x, double winPos_y, vec3& camera_dir)
{
	if (start == true) {
		m_last_pos.u = (float)winPos_x;
		m_last_pos.v = (float)winPos_y;
		start = false;
	}

	vec2 offset((float)winPos_x - m_last_pos.u, m_last_pos.v - (float)winPos_y);
	//vec2 offset((float)winPos_x - m_last_pos.u, (float)winPos_y - m_last_pos.v);

	m_last_pos.u = (float)winPos_x;
	m_last_pos.v = (float)winPos_y;

	offset.u *= sens;
	offset.v *= sens;

	// map yaw values between [-360; 360]
	yaw = fmodf((yaw + offset.u), 360.0f);
	pitch += offset.v;

	// constrain pitch values (FPS style) 
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	// convert to radians
	float ryaw = yaw * math_pi / 180.0f;
	float rpitch = pitch * math_pi / 180.0f;

	vec3 cam;
	cam.x = cosf(ryaw) * cosf(rpitch);
	cam.y = sinf(rpitch); 
	cam.z = sinf(ryaw) * cosf(rpitch);
	cam.normalize(); 

	camera_dir = cam;
}

void Camera::set_win_centre(const vec2& w_center)
{
	m_last_pos = w_center;
}
