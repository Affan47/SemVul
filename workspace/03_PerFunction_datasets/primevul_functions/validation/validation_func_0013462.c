static int vgacon_do_font_op(struct vgastate *state, char *arg, int set,
		bool ch512)
{
	unsigned short video_port_status = vga_video_port_reg + 6;
	int font_select = 0x00, beg, i;
	char *charmap;
	bool clear_attribs = false;
	if (vga_video_type != VIDEO_TYPE_EGAM) {
		charmap = (char *) VGA_MAP_MEM(colourmap, 0);
		beg = 0x0e;
	} else {
		charmap = (char *) VGA_MAP_MEM(blackwmap, 0);
		beg = 0x0a;
	}

#ifdef BROKEN_GRAPHICS_PROGRAMS


	if (!arg)
		return -EINVAL;

	vga_font_is_default = false;
	font_select = ch512 ? 0x04 : 0x00;
#else


	if (set) {
		vga_font_is_default = !arg;
		if (!arg)
			ch512 = false;
		font_select = arg ? (ch512 ? 0x0e : 0x0a) : 0x00;
	}

	if (!vga_font_is_default)
		charmap += 4 * cmapsz;
#endif

	raw_spin_lock_irq(&vga_lock);

	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x1);

	vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x04);

	vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x07);

	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x03);


	vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x02);

	vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x00);

	vga_wgfx(state->vgabase, VGA_GFX_MISC, 0x00);
	raw_spin_unlock_irq(&vga_lock);

	if (arg) {
		if (set)
			for (i = 0; i < cmapsz; i++) {
				vga_writeb(arg[i], charmap + i);
				cond_resched();
			}
		else
			for (i = 0; i < cmapsz; i++) {
				arg[i] = vga_readb(charmap + i);
				cond_resched();
			}


		if (ch512) {
			charmap += 2 * cmapsz;
			arg += cmapsz;
			if (set)
				for (i = 0; i < cmapsz; i++) {
					vga_writeb(arg[i], charmap + i);
					cond_resched();
				}
			else
				for (i = 0; i < cmapsz; i++) {
					arg[i] = vga_readb(charmap + i);
					cond_resched();
				}
		}
	}

	raw_spin_lock_irq(&vga_lock);

	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x01);

	vga_wseq(state->vgabase, VGA_SEQ_PLANE_WRITE, 0x03);

	vga_wseq(state->vgabase, VGA_SEQ_MEMORY_MODE, 0x03);

	if (set)
		vga_wseq(state->vgabase, VGA_SEQ_CHARACTER_MAP, font_select);

	vga_wseq(state->vgabase, VGA_SEQ_RESET, 0x03);


	vga_wgfx(state->vgabase, VGA_GFX_PLANE_READ, 0x00);

	vga_wgfx(state->vgabase, VGA_GFX_MODE, 0x10);

	vga_wgfx(state->vgabase, VGA_GFX_MISC, beg);


	if ((set) && (ch512 != vga_512_chars)) {
		vga_512_chars = ch512;


		inb_p(video_port_status);

		vga_wattr(state->vgabase, VGA_ATC_PLANE_ENABLE, ch512 ? 0x07 : 0x0f);


		inb_p(video_port_status);
		vga_wattr(state->vgabase, VGA_AR_ENABLE_DISPLAY, 0);
		clear_attribs = true;
	}
	raw_spin_unlock_irq(&vga_lock);

	if (clear_attribs) {
		for (i = 0; i < MAX_NR_CONSOLES; i++) {
			struct vc_data *c = vc_cons[i].d;
			if (c && c->vc_sw == &vga_con) {


				c->vc_hi_font_mask = 0x00;
				clear_buffer_attributes(c);
				c->vc_hi_font_mask = ch512 ? 0x0800 : 0;
			}
		}
	}
	return 0;
}
