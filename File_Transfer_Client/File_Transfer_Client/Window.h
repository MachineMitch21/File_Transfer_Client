#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class Window
{
private:
	GLFWwindow *w_window;
	const char* w_title;
	int w_height, w_width;

	bool w_keys[MAX_KEYS];
	bool w_buttons[MAX_BUTTONS];
public:
	Window(const char* title, int width, int height);
	
	bool init();
	void update();
	void clear();
	bool isClosed();
	bool isKeyPressed(int keycode);
	friend void window_resize_callback(GLFWwindow* w_window, int width, int height);
	friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	
	~Window();
};

