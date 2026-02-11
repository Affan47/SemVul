bios_10_07xx(struct regs *regs)
{
	unsigned short page;

#ifdef DEBUG_INT10
        dprintf("VGA Function 07: Scroll window down.\n");
#endif

	page = var_get(curr_page);

	if (AL == 0) {

		clear(page, CL, CH, DL, DH, BH);

	} else {

		scroll(page, CL, CH, DL, DH, SCROLL_DOWN, AL);

		clear(page, CL, CH, DL, CH + AL, BH);
	}
}
