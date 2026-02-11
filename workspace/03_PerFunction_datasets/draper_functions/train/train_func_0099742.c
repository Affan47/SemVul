draw_water(struct mame_bitmap* bitmap, const struct rectangle* cliprect)
{
	struct rectangle rect = *cliprect;

	int x;
	int y;

	if (rect.max_y > 127)
	{
		rect.max_y = 127;
	}

	for (y = rect.min_y; y <= rect.max_y; y++)
	{
		UINT16* p = bitmap->line[y];

		for (x = rect.min_x; x <= rect.max_x; x++)
		{
			p[x] |= 4;
		}
	}
}
