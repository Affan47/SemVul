static u8 sinp(int offset)
{
	if (iommap)

		offset <<= ioshift;

	return inb(io + offset);
}
