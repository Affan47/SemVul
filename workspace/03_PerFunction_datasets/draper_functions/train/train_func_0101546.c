fswc_add_image_y16(src_t *src, avgbmp_t *abitmap)
{
	uint16_t *bitmap = (uint16_t *) src->img;
	uint32_t i = src->width * src->height;

	if(src->length < i) return(-1);

	while(i-- > 0)
	{
		*(abitmap++) += *bitmap >> 8;
		*(abitmap++) += *bitmap >> 8;
		*(abitmap++) += *(bitmap++) >> 8;
	}

	return(0);
}
