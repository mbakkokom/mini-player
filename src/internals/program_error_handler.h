#ifndef SRC_INCLUDES_PROGRAM_ERROR_HANDLER_H_
#define SRC_INCLUDES_PROGRAM_ERROR_HANDLER_H_

enum PROGRAM_LEVEL {
	PROGRAM_LEVEL_SYSTEM = 0,
	PROGRAM_LEVEL_THREAD = 1,
	PROGRAM_LEVEL_EMULATED = 10
};

extern int program_error(enum PROGRAM_LEVEL level, const char *messages, int do_exit);
extern int program_error_n(enum PROGRAM_LEVEL level, const char *messages, int do_exit, int code);

extern int program_log(enum PROGRAM_LEVEL level, const char *messages);
extern int program_log_n(enum PROGRAM_LEVEL level, const char *messages, int code);

// derived.
extern void ogl_error_check(const char *message);

#ifdef PROGRAM_MAIN
	int glfwInitialized = 0;
#else
	extern int glfwInitialized;
#endif

#endif /* SRC_INCLUDES_PROGRAM_ERROR_HANDLER_H_ */
