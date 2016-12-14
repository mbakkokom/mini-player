#ifndef SRC_INCLUDES_PROGRAM_INPUT_HANDLER_H_
#define SRC_INCLUDES_PROGRAM_INPUT_HANDLER_H_

#include <GLFW/glfw3.h>

#ifdef PROGRAM_INPUT_HANDLER
	int input_cursor[2]={0, 0};
	int input_cursor_click=0;
	int input_cursor_outbound=0;

	volatile int thread_should_exit=0;
#else
	extern int input_cursor[2];
	extern int input_cursor_click;
	extern int input_cursor_outbound;

	extern void program_mouse_position(GLFWwindow *window, double xpos, double ypos);
	extern void program_mouse_click(GLFWwindow* window, int button, int action, int mods);
	extern void program_mouse_areacheck(GLFWwindow *window, int entered);
	extern void program_window_resize(GLFWwindow* window, int width, int height);
	extern void program_window_close(GLFWwindow* window);
#endif


#endif /* SRC_INCLUDES_PROGRAM_INPUT_HANDLER_H_ */
