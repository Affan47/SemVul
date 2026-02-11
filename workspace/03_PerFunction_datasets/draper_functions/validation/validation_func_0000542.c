program_write_word_32le(offs_t address, uint16_t data)
{
	if (address & 2)
	{
		psx_hw_write(address, data<<16, 0x0000ffff);
		return;
	}

	psx_hw_write(address, data, 0xffff0000);
}
