static int vgacon_adjust_height(struct vc_data *vc, unsigned fontheight)
{
	unsigned char ovr, vde, fsr;
	int rows, maxscan, i;

	rows = vc->vc_scan_lines / fontheight;
	maxscan = rows * fontheight - 1;


	raw_spin_lock_irq(&vga_lock);
	outb_p(0x07, vga_video_port_reg);
	ovr = inb_p(vga_video_port_val);
	outb_p(0x09, vga_video_port_reg);
	fsr = inb_p(vga_video_port_val);
	raw_spin_unlock_irq(&vga_lock);

	vde = maxscan & 0xff;
	ovr = (ovr & 0xbd) +
	    ((maxscan & 0x100) >> 7) + ((maxscan & 0x200) >> 3);
	fsr = (fsr & 0xe0) + (fontheight - 1);

	raw_spin_lock_irq(&vga_lock);
	outb_p(0x07, vga_video_port_reg);
	outb_p(ovr, vga_video_port_val);
	outb_p(0x09, vga_video_port_reg);
	outb_p(fsr, vga_video_port_val);
	outb_p(0x12, vga_video_port_reg);
	outb_p(vde, vga_video_port_val);
	raw_spin_unlock_irq(&vga_lock);
	vga_video_font_height = fontheight;

	for (i = 0; i < MAX_NR_CONSOLES; i++) {
		struct vc_data *c = vc_cons[i].d;

		if (c && c->vc_sw == &vga_con) {
			if (con_is_visible(c)) {

				cursor_size_lastfrom = 0;
				cursor_size_lastto = 0;
				c->vc_sw->con_cursor(c, CM_DRAW);
			}
			c->vc_font.height = fontheight;
			vc_resize(c, 0, rows);
		}
	}
	return 0;
}
