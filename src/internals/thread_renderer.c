#include <malloc.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <pthread.h>

#define THREAD_INSTANCES
#define RENDER_THREAD
#include "program_error_handler.h"
#include "program_messages.h"
#include "render_internals.h"
#include "render_init.h"
#include "render_settings.h"
#include "thread_settings.h"

void *thread_renderer(void *arguments) {

	glfwMakeContextCurrent(window);

	render_init();

	for (;;) {

		if (thread_should_exit == 1) break;

		render_init_rebind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, window_fb_width, window_fb_height, 0, 1, -1);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		//

		glEnable(GL_TEXTURE_2D);
		//glEnable(GL_BLEND);

		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, render_screen_pbo);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, window_texture_width, window_texture_height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, window_fb_height_f);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(window_fb_width_f,  window_fb_height_f);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(window_fb_width_f,  0.0f);

		glEnd();

		//

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);

		//glPopMatrix(); // cause underflow
		glMatrixMode(GL_MODELVIEW);

		ogl_error_check("Popping GL_PROJECTION.");

		// Swap buffers
		glfwSwapBuffers(window);
		//glfwPollEvents();

	}

	program_log(PROGRAM_LEVEL_EMULATED, "Break from render loop.");

	return NULL;
}
