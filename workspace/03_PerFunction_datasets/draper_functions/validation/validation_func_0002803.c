draw_phasor(struct mame_bitmap* bitmap)
{
	int i;

	for (i = 128; i < 240; i++)
	{
		if (i >= get_sprite_vpos(13))
		{
			plot_pixel(bitmap, 2 * i + 0, i, 7);
			plot_pixel(bitmap, 2 * i + 1, i, 7);
			plot_pixel(bitmap, 2 * (255 - i) + 0, i, 7);
			plot_pixel(bitmap, 2 * (255 - i) + 1, i, 7);
		}
	}
}
