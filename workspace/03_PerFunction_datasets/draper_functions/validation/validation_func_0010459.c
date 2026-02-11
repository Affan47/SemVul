lsr_write_fixed_clamp(GF_LASeRCodec *lsr, Fixed f, const char *name)
{
#ifdef GPAC_FIXED_POINT
	s32 val = f >> 8;
#else
	s32 val = (u32) (255 * f);
#endif
	if (val<0) val = 0;
	else if (val>255) val = 255;
	GF_LSR_WRITE_INT(lsr, (u32) val, 8, name);
}
