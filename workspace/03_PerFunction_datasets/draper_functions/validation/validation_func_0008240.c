exedexes_draw_sprites(struct mame_bitmap *bitmap, int priority)
{
	int offs;

	if (!objon) return;

	priority = priority ? 0x40 : 0x00;

	for (offs = spriteram_size - 32;offs >= 0;offs -= 32)
	{
		if ((buffered_spriteram[offs + 1] & 0x40) == priority)
		{
			int code,color,flipx,flipy,sx,sy;

			code = buffered_spriteram[offs];
			color = buffered_spriteram[offs + 1] & 0x0f;
			flipx = buffered_spriteram[offs + 1] & 0x10;
			flipy = buffered_spriteram[offs + 1] & 0x20;
			sx = buffered_spriteram[offs + 3] - ((buffered_spriteram[offs + 1] & 0x80) << 1);
			sy = buffered_spriteram[offs + 2];

			drawgfx(bitmap,Machine->gfx[3],
					code,
					color,
					flipx,flipy,
					sx,sy,
					&Machine->visible_area,TRANSPARENCY_PEN,0);
		}
	}
}
