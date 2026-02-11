cursorsprite (void)
{
	if (!dmaen (DMA_SPRITE) || first_planes_vpos == 0)
		return;
	sprite_0 = spr[0].pt;
	sprite_0_height = spr[0].vstop - spr[0].vstart;
	sprite_0_colors[0] = 0;
	sprite_0_doubled = 0;
	if (sprres == 0)
		sprite_0_doubled = 1;
	if (currprefs.chipset_mask & CSMASK_AGA) {
		int sbasecol = ((bplcon4 >> 4) & 15) << 4;
		sprite_0_colors[1] = current_colors.color_regs_aga[sbasecol + 1];
		sprite_0_colors[2] = current_colors.color_regs_aga[sbasecol + 2];
		sprite_0_colors[3] = current_colors.color_regs_aga[sbasecol + 3];
	} else {
		sprite_0_colors[1] = xcolors[current_colors.color_regs_ecs[17]];
		sprite_0_colors[2] = xcolors[current_colors.color_regs_ecs[18]];
		sprite_0_colors[3] = xcolors[current_colors.color_regs_ecs[19]];
	}
	sprite_0_width = sprite_width;
	if (currprefs.input_tablet && currprefs.input_magic_mouse) {
		if (currprefs.input_magic_mouse_cursor == MAGICMOUSE_HOST_ONLY && mousehack_alive ())
			magic_sprite_mask &= ~1;
		else
			magic_sprite_mask |= 1;
	}
}
