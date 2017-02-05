#include "Window.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Window::Window(const char* title, int width, int height)
{
	w_title = title;
	w_height = height;
	w_width = width;
	if (!init()) {
		std::cout << "Success!!" << std::endl;
	}

	for (int i = 0; i < MAX_KEYS; i++) {
		w_keys[i] = false;
	}

	for (int i = 0; i < MAX_BUTTONS; i++) {
		w_buttons[i] = false;
	}
}

bool Window::init() {

	if (!glfwInit()) {
		std::cout << "-GLFW failed to initialize-" << std::endl;
		return false;
	}

	w_window = glfwCreateWindow(w_width, w_height, w_title, NULL, NULL);

	if (!w_window) {
		std::cout << "-Failed to create window-" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(w_window);
	glfwSetKeyCallback(w_window, key_callback);
	glfwSetFramebufferSizeCallback(w_window, window_resize_callback);
	glfwSetWindowUserPointer(w_window, this);

	return true;
}

void Window::update() {
	glfwSwapBuffers(w_window);
	glfwPollEvents();
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::isClosed() {
	return glfwWindowShouldClose(w_window);
}

bool Window::isKeyPressed(int key) {
	return w_keys[key];
}

void window_resize_callback(GLFWwindow* w_window, int width, int height) {
	
	glViewport(0, 0, width, height);

}

void key_callback(GLFWwindow* w_window, int key, int scancode, int action, int mods) {
	Window* win = (Window*)glfwGetWindowUserPointer(w_window);
	win->w_keys[key] = action != GLFW_RELEASE;
}

Window::~Window()
{
	glfwDestroyWindow(w_window);
	glfwTerminate();
}
