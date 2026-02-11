detect_available_resolutions(void)
{
	SDL_Rect **modes;
	screen_resolution resolution_holder;
	int i, j, merged_size;
	char *res[64];


	modes = SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
	if (modes == (SDL_Rect**) -1) {
		ErrorMessage(__FUNCTION__,
			"SDL reports all resolutions are supported in fullscreen mode.\n"
			"Please use -r WIDTHxHEIGHT to specify any one you like.\n"
			"Defaulting to a sane one for now\n", NO_NEED_TO_INFORM, IS_WARNING_ONLY);
			screen_resolutions[0] =	(screen_resolution) {DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "", TRUE};
			i = 1;
	} else {

		for (i = 0; modes[i] && i < MAX_RESOLUTIONS; ++i) {
			res[i] = (char *) malloc(32);
			sprintf(res[i], "%d x %d", modes[i]->w, modes[i]->h);
			screen_resolutions[i] = (screen_resolution) {modes[i]->w, modes[i]->h, res[i], TRUE};
		}
	}


	for (j = 0; j < sizeof(hard_resolutions) / sizeof(hard_resolutions[0]) && i + j < MAX_RESOLUTIONS; j++) {
		screen_resolutions[i + j] = hard_resolutions[j];
	}


	merged_size = i + min(sizeof(hard_resolutions) / sizeof(hard_resolutions[0]), j);
	for (i = 0; i < merged_size; i++) {
		for (j = 0; j < merged_size - 1; j++) {

			if (screen_resolutions[j].xres < screen_resolutions[j + 1].xres ||
					(screen_resolutions[j].xres == screen_resolutions[j + 1].xres &&
					screen_resolutions[j].yres < screen_resolutions[j +1].yres)) {
				resolution_holder = screen_resolutions[j + 1];
				screen_resolutions[j + 1] = screen_resolutions[j];
				screen_resolutions[j] = resolution_holder;


			} else if (screen_resolutions[j].xres == screen_resolutions[j + 1].xres &&
					screen_resolutions[j].yres == screen_resolutions[j + 1].yres)
				screen_resolutions[j + 1] = (screen_resolution) {-1, -1, "", FALSE};
		}
	}


	screen_resolutions[i - 1] = (screen_resolution) {-1, -1, "", FALSE};
}
