#include "program_error_handler.h"

#include <stdio.h>
#include <stdlib.h>

#include <GLFW/glfw3.h>

int program_error(enum PROGRAM_LEVEL level, const char *messages, int do_exit) {
	fprintf(stderr, "[ERROR:%d] %s\n", level, messages);
	if (do_exit == 1) {
		if (glfwInitialized == 1) glfwTerminate();
		exit(EXIT_SUCCESS);
	}

	return 0;
}

int program_error_n(enum PROGRAM_LEVEL level, const char *messages, int do_exit, int code) {
	fprintf(stderr, "[ERROR:%d] %s (code=%d)\n", level, messages, code);
	if (do_exit == 1) {
		if (glfwInitialized == 1) glfwTerminate();
		exit(EXIT_SUCCESS);
	}

	return 0;
}

int program_log(enum PROGRAM_LEVEL level, const char *messages) {
	fprintf(stdout, "[LOG:%d] %s\n", level, messages);

	return 0;
}

int program_log_n(enum PROGRAM_LEVEL level, const char *messages, int code) {
	fprintf(stdout, "[LOG:%d] %s (code=%d)\n", level, messages, code);

	return 0;
}

void ogl_error_check(const char *message) {
	GLenum err = glGetError();
	if (err != 0)
		program_error_n(PROGRAM_LEVEL_SYSTEM, message, 1, err);
}
