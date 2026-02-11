mariner_draw_background(struct mame_bitmap *bitmap)
{
	UINT8 x;
	UINT8 *prom;


	prom = memory_region(REGION_USER1);

	if (flip_screen_x)
	{
		for (x = 0; x < 32; x++)
		{
			int color;


			if (x == 0)
				color = 0;
			else
				color = prom[0x20 + x - 1];

			plot_box(bitmap, 8 * (31 - x), 0, 8, 256, Machine->pens[BACKGROUND_COLOR_BASE + color]);
		}
	}
	else
	{
		for (x = 0; x < 32; x++)
		{
			int color;


			if (x == 31)
				color = 0;
			else
				color = prom[x + 1];

			plot_box(bitmap, 8 * x, 0, 8, 256, Machine->pens[BACKGROUND_COLOR_BASE + color]);
		}
	}
}
