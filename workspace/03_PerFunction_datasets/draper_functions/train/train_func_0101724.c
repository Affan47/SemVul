PBI_XLD_D1ffPutByte(UBYTE byte)
{
	int result = 0;
	if (xld_d_enabled && byte == DISK_MASK) {
		memcpy(MEMORY_mem + 0xd800, diskrom, 0x800);
		D(printf("DISK rom activated\n"));
	}
	else if (byte == MODEM_MASK) {
		memcpy(MEMORY_mem + 0xd800, voicerom + 0x800, 0x800);
		D(printf("MODEM rom activated\n"));
	}
	else if (byte == VOICE_MASK) {
		memcpy(MEMORY_mem + 0xd800, voicerom, 0x800);
		D(printf("VOICE rom activated\n"));
	}
	else result = PBI_NOT_HANDLED;
	return result;
}
