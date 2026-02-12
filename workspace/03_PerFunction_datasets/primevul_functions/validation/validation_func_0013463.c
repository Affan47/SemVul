static void vga_vesa_blank(struct vgastate *state, int mode)
{

	if (!vga_vesa_blanked) {
		raw_spin_lock_irq(&vga_lock);
		vga_state.SeqCtrlIndex = vga_r(state->vgabase, VGA_SEQ_I);
		vga_state.CrtCtrlIndex = inb_p(vga_video_port_reg);
		vga_state.CrtMiscIO = vga_r(state->vgabase, VGA_MIS_R);
		raw_spin_unlock_irq(&vga_lock);

		outb_p(0x00, vga_video_port_reg);
		vga_state.HorizontalTotal = inb_p(vga_video_port_val);
		outb_p(0x01, vga_video_port_reg);
		vga_state.HorizDisplayEnd = inb_p(vga_video_port_val);
		outb_p(0x04, vga_video_port_reg);
		vga_state.StartHorizRetrace = inb_p(vga_video_port_val);
		outb_p(0x05, vga_video_port_reg);
		vga_state.EndHorizRetrace = inb_p(vga_video_port_val);
		outb_p(0x07, vga_video_port_reg);
		vga_state.Overflow = inb_p(vga_video_port_val);
		outb_p(0x10, vga_video_port_reg);
		vga_state.StartVertRetrace = inb_p(vga_video_port_val);
		outb_p(0x11, vga_video_port_reg);
		vga_state.EndVertRetrace = inb_p(vga_video_port_val);
		outb_p(0x17, vga_video_port_reg);
		vga_state.ModeControl = inb_p(vga_video_port_val);
		vga_state.ClockingMode = vga_rseq(state->vgabase, VGA_SEQ_CLOCK_MODE);
	}


	raw_spin_lock_irq(&vga_lock);
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, vga_state.ClockingMode | 0x20);


	if ((vga_state.CrtMiscIO & 0x80) == 0x80)
		vga_w(state->vgabase, VGA_MIS_W, vga_state.CrtMiscIO & 0xEF);


	if (mode & VESA_VSYNC_SUSPEND) {
		outb_p(0x10, vga_video_port_reg);
		outb_p(0xff, vga_video_port_val);
		outb_p(0x11, vga_video_port_reg);
		outb_p(0x40, vga_video_port_val);
		outb_p(0x07, vga_video_port_reg);
		outb_p(vga_state.Overflow | 0x84, vga_video_port_val);
	}

	if (mode & VESA_HSYNC_SUSPEND) {


		outb_p(0x04, vga_video_port_reg);
		outb_p(0xff, vga_video_port_val);
		outb_p(0x05, vga_video_port_reg);
		outb_p(0x00, vga_video_port_val);
	}


	vga_w(state->vgabase, VGA_SEQ_I, vga_state.SeqCtrlIndex);
	outb_p(vga_state.CrtCtrlIndex, vga_video_port_reg);
	raw_spin_unlock_irq(&vga_lock);
}
