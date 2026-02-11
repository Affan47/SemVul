mark_toaplan1_sprite_priority(void)
{
	int priority;
	offs_t offs;

	for (priority = 0; priority < 16; priority++)
		sprite_priority[priority] = 0;

	for (offs = 0; offs < (TOAPLAN1_SPRITERAM_SIZE/2); offs += 4)
	{
		if ((buffered_spriteram16[offs] & 0x8000) == 0)
		{
			priority = (buffered_spriteram16[offs + 1] & 0xf000) >> 12;
			sprite_priority[priority] = display_sprites;
		}
	}
}
