#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define PROGRAM_INPUT_HANDLER
#include "program_input_handler.h"
#include "program_error_handler.h"
#include "render_settings.h"
#include "thread_settings.h"

void program_mouse_position(GLFWwindow *window, double xpos, double ypos) {
	if (input_cursor_outbound) return;
	input_cursor[0] = ((float)xpos / window_fb_width) * window_texture_width;
	input_cursor[1] = ((float)ypos / window_fb_height) * window_texture_height;
	//printf("Checking on div: %f.", (((float)xpos / window_fb_height)));
	//printf("Got cursor at %dx%d.\n", input_cursor[0], input_cursor[1]);
	return;
}

void program_mouse_click(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		input_cursor_click = 1;
		//printf("Got click at %dx%d.\n", input_cursor_click[0], input_cursor_click[1]);
	} else if (action == GLFW_RELEASE) {
		input_cursor_click = 0;
	}
	return;
}

void program_mouse_areacheck(GLFWwindow *window, int entered) {
	if (entered) input_cursor_outbound = 0;
	else {
		input_cursor_outbound = 1;
		input_cursor[0] = -1;
		input_cursor[1] = -1;
	}
	return;
}

void program_window_resize(GLFWwindow* window, int width, int height) {
	glfwGetFramebufferSize(window, &window_fb_width, &window_fb_height);
	window_fb_width_f = (float) window_fb_width;
	window_fb_height_f = (float) window_fb_height;
	return;
}

void program_window_close(GLFWwindow* window) {
	thread_should_exit = 1;
	return;
}
