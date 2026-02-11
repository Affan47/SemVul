confirm(void)
{

	for(int disk = 0; disk < PARTS; disk++) {
		strncpy(gui_options.disks[disk].partID, part_id[disk], sizeof(gui_options.disks[disk].partID));
		gui_options.disks[disk].present = getSelected(PARTS_PRESENT[disk]);
		gui_options.disks[disk].readonly = getSelected(PARTS_READONLY[disk]);
		gui_options.disks[disk].byteswap = getSelected(PARTS_BYTESWAP[disk]);
	}

	bx_options = gui_options;
}
