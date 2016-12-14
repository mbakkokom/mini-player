#ifndef SRC_INCLUDES_RENDER_SETTINGS_
#define SRC_INCLUDES_RENDER_SETTINGS_

#define RENDER_CONTEXT_VERSION_MAJOR 2
#define RENDER_CONTEXT_VERSION_MINOR 1

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 650

#ifdef PROGRAM_MAIN
	GLFWwindow *window;

	const char *window_title  = "Hello World!";

	int		window_fb_width,
			window_fb_height;
	float	window_fb_width_f,
			window_fb_height_f;
	int		window_texture_width,		// should be half of window_fb_*_f
			window_texture_height;

	int 	RENDER_SAMPLES = 4,
			RENDER_VSYNC = 1;

	float	render_clearColor[4] =
			{ 0.90f, 0.35f, 0.45f, 0.0f };
#else
	extern GLFWwindow *window;

	extern const char *window_title;

	extern int		window_fb_width,
					window_fb_height;
	extern float	window_fb_width_f,
					window_fb_height_f;
	extern int		window_texture_width,		// should be half of window_fb_*_f
					window_texture_height;

	extern int 		RENDER_SAMPLES,
					RENDER_VSYNC;

	extern float	render_clearColor[4];
#endif

#endif /* SRC_INCLUDES_RENDER_SETTINGS_ */
