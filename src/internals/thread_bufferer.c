#include <pthread.h>

#define THREAD_INSTANCES
#include "program_input_handler.h"
#include "program_error_handler.h"
#include "render_internals.h"
#include "render_settings.h"
#include "thread_settings.h"

int pre_offset = 0;

void color_fill() {
	if (input_cursor_outbound || input_cursor_click != 1) return;

	if (pre_offset == 0) {
		pre_offset = (window_texture_width * 4);
	}

	int pixel_offset = (pre_offset * input_cursor[1]) +
			 	 	 (input_cursor[0] * 4); // 4 for RGBA

	if (pixel_offset > render_screen_buffer_size) return;

	render_screen_buffer[pixel_offset + 0] = 255;
	render_screen_buffer[pixel_offset + 1] = 0;
	render_screen_buffer[pixel_offset + 2] = 0;
	render_screen_buffer[pixel_offset + 3] = 0;		// Alpha.

	return;
}

void *thread_bufferer(void *arguments) {

	for(;;) {
		if(thread_should_exit == 1) break;

		glfwPollEvents();

		pthread_mutex_lock(&render_screen_buffer_mutex);
		color_fill();
		pthread_mutex_unlock(&render_screen_buffer_mutex);
	}

	return 0;
}
