cc_usb_read_memory(struct cc_usb *cc, uint16_t addr, uint8_t *bytes, int len)
{
	int	i;
	cc_queue_read(cc, bytes, len);
	cc_usb_printf(cc, "I %x %x\n", len, addr);
	cc_usb_sync(cc);
	for (i = 0; i < len; i++) {
		if ((i & 15) == 0) {
			if (i)
				ccdbg_debug(CC_DEBUG_MEMORY, "\n");
			ccdbg_debug(CC_DEBUG_MEMORY, "\t%04x", addr + i);
		}
		ccdbg_debug(CC_DEBUG_MEMORY, " %02x", bytes[i]);
	}
	ccdbg_debug(CC_DEBUG_MEMORY, "\n");
	return 0;
}
