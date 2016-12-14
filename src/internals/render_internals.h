#ifndef INTERNALS_RENDER_INTERNALS_H_
#define INTERNALS_RENDER_INTERNALS_H_

#include <GL/gl.h>
#include <pthread.h>

#ifdef RENDER_THREAD
	GLubyte	*render_screen_buffer;
	int		render_screen_buffer_size=0,
			render_screen_buffer_init=0;
	pthread_mutex_t render_screen_buffer_mutex;

	GLuint 	render_screen_pbo;
	int 	render_screen_pbo_ready;
	pthread_mutex_t render_screen_pbo_mutex;

	GLuint 	render_screen_texture;
#else
	extern GLubyte	*render_screen_buffer;
	extern int 	render_screen_buffer_size,
				render_screen_buffer_init;
	extern pthread_mutex_t render_screen_buffer_mutex;

	extern GLuint 	render_screen_pbo;
	extern int 		render_screen_pbo_ready;
	extern pthread_mutex_t render_screen_pbo_mutex;

	extern GLuint 	render_screen_texture;
#endif

#endif /* INTERNALS_RENDER_INTERNALS_H_ */
