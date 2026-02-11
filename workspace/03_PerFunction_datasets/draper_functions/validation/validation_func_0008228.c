cavan_display_test_main(int argc, char *argv[])
{
	int i, j, width, height;
	struct cavan_display_device *display;
	cavan_display_color_t color_map[3][3];

	display = cavan_fb_display_start();
	if (display == NULL)
	{
		pr_red_info("cavan_fb_display_start");
		return -EFAULT;
	}

	color_map[0][0] = display->build_color(display, 1.0, 0.0, 0.0, 1.0);
	color_map[0][1] = display->build_color(display, 0.0, 1.0, 0.0, 1.0);
	color_map[0][2] = display->build_color(display, 0.0, 0.0, 1.0, 1.0);

	color_map[1][0] = display->build_color(display, 1.0, 1.0, 1.0, 1.0);
	color_map[1][1] = display->build_color(display, 0.0, 0.0, 0.0, 1.0);
	color_map[1][2] = display->build_color(display, 0.5, 0.5, 0.5, 1.0);

	color_map[2][0] = display->build_color(display, 0.0, 1.0, 1.0, 1.0);
	color_map[2][1] = display->build_color(display, 1.0, 0.0, 1.0, 1.0);
	color_map[2][2] = display->build_color(display, 1.0, 1.0, 0.0, 1.0);

	width = display->xres / 3;
	height = display->yres / 3;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			display->set_color(display, color_map[i][j]);
			display->fill_rect(display, i * width, j * height, width, height, display->pen_color);
		}
	}

	cavan_display_refresh(display);

	cavan_display_stop(display);
	display->destroy(display);

	return 0;
}
