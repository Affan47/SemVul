static void soutp(int offset, u8 value)
{
	if (iommap)

		offset <<= ioshift;

	outb(value, io + offset);
}
