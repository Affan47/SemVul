static int vgacon_set_origin(struct vc_data *c)
{
	if (vga_is_gfx ||
	    (console_blanked && !vga_palette_blanked))
		return 0;
	c->vc_origin = c->vc_visible_origin = vga_vram_base;
	vga_set_mem_top(c);
	vga_rolled_over = 0;
	return 1;
}
