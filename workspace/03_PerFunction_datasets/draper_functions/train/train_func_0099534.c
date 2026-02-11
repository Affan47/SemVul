vdp_register_w(int data)
{
	static const UINT8 is_important[32] = { 0,0,1,1,1,1,0,1,0,0,0,1,0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	UINT8 regnum = (data & 0x1f00) >> 8;
	UINT8 regdat = (data & 0x00ff);

	segac2_vdp_regs[regnum] = regdat;


	if (!internal_vblank && is_important[regnum])
		force_partial_update((cpu_getscanline())+ scanbase);


	switch (regnum)
	{
		case 0x01:
			if (regdat & 8)
				usrintf_showmessage("Video height = 240!");
			break;

		case 0x02:
			vdp_scrollabase = (regdat & 0x38) << 10;
			break;

		case 0x03:
			vdp_windowbase = (regdat & 0x3e) << 10;
			break;

		case 0x04:
			vdp_scrollbbase = (regdat & 0x07) << 13;
			break;

		case 0x05:
			vdp_spritebase = (regdat & 0x7e) << 9;
			break;

		case 0x07:
			bgcol = regdat & 0x3f;
			break;

		case 0x0b:
		{
			static const UINT16 mask_table[4] = { 0x000, 0x007, 0xff8, 0xfff };
			vdp_vscrollmode = (regdat & 0x04) >> 2;

			vdp_hscrollmask = mask_table[regdat & 3];
			vdp_hscrollsize = 4 * ((vdp_hscrollmask < 224) ? (vdp_hscrollmask + 1) : 224);
			break;
		}

		case 0x0c:


			break;

		case 0x0d:
			vdp_hscrollbase = (regdat & 0x3f) << 10;
			break;

		case 0x10:
		{
			static const UINT8 size_table[4] = { 32, 64, 128, 128 };
			scrollwidth = size_table[regdat & 0x03];
			scrollheight = size_table[(regdat & 0x30) >> 4];
			break;
		}

		case 0x11:
			window_right = regdat & 0x80;
			window_hpos = (regdat & 0x1f) << 4;
			break;

		case 0x12:
			window_down = regdat & 0x80;
			window_vpos = (regdat & 0x1f) << 3;
			break;
	}
}
