putPixel(memptr vwk, memptr dst, int32 x, int32 y,
	uint32 color)
{
	if (vwk & 1)
		return 0;

	if (dst)
		return VdiDriver::putPixel(vwk, dst, x, y, color);

	if (surface) {
		hsPutPixel(x, y, color);
		surface->setDirtyRect(x,y,1,1);
	}

	return 1;
}
