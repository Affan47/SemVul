static int sisusb_clear_vram(struct sisusb_usb_data *sisusb,
		u32 address, int length)
{
	int ret, i;
	ssize_t j;

	if (address < sisusb->vrambase)
		return 1;

	if (address >= sisusb->vrambase + sisusb->vramsize)
		return 1;

	if (address + length > sisusb->vrambase + sisusb->vramsize)
		length = sisusb->vrambase + sisusb->vramsize - address;

	if (length <= 0)
		return 0;


	i = sisusb_alloc_outbuf(sisusb);
	if (i < 0)
		return -EBUSY;

	memset(sisusb->obuf[i], 0, sisusb->obufsize);


	ret = sisusb_write_mem_bulk(sisusb, address, NULL, length, NULL, i, &j);


	sisusb_free_outbuf(sisusb, i);

	return ret;
}
