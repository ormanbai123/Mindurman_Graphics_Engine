#pragma once

#include "Shader.h"
#include <GLFW/glfw3.h>
#include "Matrix.h"

#include "Textures.h"

#include "Model.h"
#include "Camera.h"

//#define pi 3.14159f

class window {

public:
	window(int width, int height, const char title[]);
	~window();
	void begin();
private:
	int winHeight = 0; int winWidth = 0; float winaspectRatio = 0;
	GLFWwindow* m_win = nullptr;                       // Window pointer
	static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
	static void mouse_callback(GLFWwindow* win, double x_pos, double y_pos);
	void cls();
	void input(GLFWwindow* win);

	vec3 light = vec3(0.0f, 0.0f, 0.0f);
    //Camera fps_cam{vec3(0.0f, 0.0f, 2.0f), vec3(0.0f, 0.0f, -1.0f) , vec2(winWidth/2.0f, winHeight/2.0f)};
};