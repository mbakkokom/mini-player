#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <pthread.h>

#define PROGRAM_MAIN
#include "internals/program_error_handler.h"
#include "internals/program_input_handler.h"
#include "internals/program_messages.h"
#include "internals/render_settings.h"
#include "internals/render_init.h"
#include "internals/thread_settings.h"

int main(int argc, char *argv[]) {

	if( !glfwInit() ) program_error(PROGRAM_LEVEL_SYSTEM, GLFW_INIT_FAILED, 1);

	glfwInitialized = 1;

	glfwWindowHint(GLFW_SAMPLES, RENDER_SAMPLES);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, RENDER_CONTEXT_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, RENDER_CONTEXT_VERSION_MINOR);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow( WINDOW_WIDTH, WINDOW_HEIGHT, window_title, NULL, NULL);
	if( window == NULL ) program_error(PROGRAM_LEVEL_SYSTEM, GLFW_WINDOW_FAILED, 1);

	glfwMakeContextCurrent(window);
	
	GLenum err = glewInit();
	if (err != GLEW_OK) program_error_n(PROGRAM_LEVEL_SYSTEM, GLEW_INIT_FAILED, 1, err);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);

	glClearColor(
			render_clearColor[0],
			render_clearColor[1],
			render_clearColor[2],
			render_clearColor[3]);

	glfwGetFramebufferSize(window, &window_fb_width, &window_fb_height);
	window_fb_width_f = (float) window_fb_width;
	window_fb_height_f = (float) window_fb_height;

	window_texture_width = 128;
	window_texture_height = 128;

	glfwSetCursorPosCallback(window, program_mouse_position);
	glfwSetCursorEnterCallback(window, program_mouse_areacheck);
	glfwSetMouseButtonCallback(window, program_mouse_click);
	glfwSetWindowSizeCallback(window, program_window_resize);
	glfwSetWindowCloseCallback(window, program_window_close);

	glfwSwapInterval(RENDER_VSYNC);

	err = glGetError();
	if (err != GL_NO_ERROR) program_error_n(PROGRAM_LEVEL_SYSTEM, OGL_GENERIC_ERROR, 1, err);

	//
	pthread_t 	renderer_t,
				bufferer_t;

	render_init();

	if(pthread_create(&renderer_t, NULL, thread_renderer, NULL))
		program_error(PROGRAM_LEVEL_SYSTEM, THREAD_RENDERER_SPAWN_ERROR, 1);
	if(pthread_create(&bufferer_t, NULL, thread_bufferer, NULL))
		program_error(PROGRAM_LEVEL_SYSTEM, THREAD_BUFFERER_SPAWN_ERROR, 1);

	if(pthread_join(renderer_t, NULL))
		program_error(PROGRAM_LEVEL_SYSTEM, THREAD_RENDERER_JOIN_ERROR, 1);
	if(pthread_join(bufferer_t, NULL))
		program_error(PROGRAM_LEVEL_SYSTEM, THREAD_BUFFERER_JOIN_ERROR, 1);


	glfwMakeContextCurrent(window);

	render_init_free();

	glfwDestroyWindow(window);
	glfwTerminate();

	glfwInitialized = 0;

	program_log(PROGRAM_LEVEL_EMULATED, "Threads exited gracefully and glfw is terminated.");

	exit(EXIT_SUCCESS);

	return 0;
}
