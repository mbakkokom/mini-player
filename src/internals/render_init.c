#include <stdlib.h>

#include <malloc.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "render_settings.h"
#include "render_internals.h"
#include "program_input_handler.h"
#include "program_error_handler.h"
#include "program_messages.h"
#include "thread_settings.h"

#include <pthread.h>

int p=0;

void colorful() {
	time_t t;
	srand((unsigned) time(&t));
	int i;
	for (i=0; i<render_screen_buffer_size; i++) {
		render_screen_buffer[i] = 255; //(p) + (rand() % 255);
	}
}

void render_init() {
	pthread_mutex_lock(&render_screen_buffer_mutex);
	pthread_mutex_lock(&render_screen_pbo_mutex);

	render_screen_buffer_size = window_texture_width * window_texture_height * 4; // 4 for RGBA
	render_screen_buffer = malloc(render_screen_buffer_size * sizeof(GLubyte));

	if (render_screen_buffer == NULL)
		program_error(PROGRAM_LEVEL_SYSTEM, "Unable to allocate using `calloc`.", 0);
	else
		render_screen_buffer_init = 1;

	colorful();

	glGenBuffers(1, &render_screen_pbo);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, render_screen_pbo);
	glBufferData(
			GL_PIXEL_UNPACK_BUFFER,
			render_screen_buffer_size,
			render_screen_buffer,
			GL_DYNAMIC_DRAW);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		program_error_n(PROGRAM_LEVEL_SYSTEM, OGL_BUFFER_CREATION_ERROR, 1, err);
	else
		render_screen_pbo_ready = 1;

	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glGenTextures(1, &render_screen_texture);

	glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			window_texture_width,
			window_texture_height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			NULL);

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	ogl_error_check("Init after generate texture image.");

	pthread_mutex_unlock(&render_screen_buffer_mutex);
	pthread_mutex_unlock(&render_screen_pbo_mutex);

	return;
}

void render_init_rebind() {
	pthread_mutex_lock(&render_screen_buffer_mutex);
	pthread_mutex_lock(&render_screen_pbo_mutex);

	if (render_screen_buffer_init != 1)
		program_error(PROGRAM_LEVEL_SYSTEM, "Rebind operation before initialization.", 1);

	ogl_error_check("Before glBindBuffer, start of rebind.");

	//color_fill(); // for testing only. pixel draw.

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, render_screen_pbo);
	glBufferSubData(
			GL_PIXEL_UNPACK_BUFFER,
			0,
			render_screen_buffer_size,
			render_screen_buffer);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		program_error_n(PROGRAM_LEVEL_SYSTEM, OGL_BUFFER_CREATION_ERROR, 1, err);

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	pthread_mutex_unlock(&render_screen_buffer_mutex);
	pthread_mutex_unlock(&render_screen_pbo_mutex);

	return;
}

void render_init_free() {
	pthread_mutex_lock(&render_screen_buffer_mutex);
	pthread_mutex_lock(&render_screen_pbo_mutex);

	if (render_screen_buffer_init != 1 && render_screen_pbo_ready != 1)
		program_error(PROGRAM_LEVEL_SYSTEM, "Free operation before initialization.", 1);

	free(render_screen_buffer);
	glDeleteBuffers(1, &render_screen_pbo);

	render_screen_buffer_size=0;
	render_screen_buffer_init=0;
	render_screen_pbo_ready=0;

	pthread_mutex_unlock(&render_screen_buffer_mutex);
	pthread_mutex_unlock(&render_screen_pbo_mutex);

	program_log(PROGRAM_LEVEL_SYSTEM, "All memory freed.");

	return;
}
