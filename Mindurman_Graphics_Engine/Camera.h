#pragma once

#include "Matrix.h"

class Camera {

public:
	Camera(const vec3& cam_pos, const vec3& cam_dir, const vec2& win_centre);

    void input_mouse(double winPos_x, double winPos_y, vec3& camera_dir);

	void set_vec_Up();
	void set_win_centre(const vec2& w_center);

	vec3 vDir; vec3 vPos; vec3 vUp;

	float sens = 0.1f;
private:
	bool start = true;
	//vec3 pos; //vec3 dir;
	vec2 m_last_pos;
	float yaw = -90.0f; float pitch = 0.0f; float roll = 0.0f;
};