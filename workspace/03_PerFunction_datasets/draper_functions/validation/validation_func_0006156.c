close_bitstream (struct JPEG_ENCODER_STRUCTURE * jpeg_encoder_structure, UINT8 *output_ptr)
{
	UINT16 i, count;
	UINT8 *ptr;


	if (jpeg_encoder_structure->bitindex > 0)
	{
		jpeg_encoder_structure->lcode <<= (32 - jpeg_encoder_structure->bitindex);
		count = (jpeg_encoder_structure->bitindex + 7) >> 3;

		ptr = (UINT8 *) &jpeg_encoder_structure->lcode + 3;

		for (i=count; i>0; i--)
		{
			if ((*output_ptr++ = *ptr--) == 0xff)
				*output_ptr++ = 0;
		}
	}


	*output_ptr++ = 0xFF;
	*output_ptr++ = 0xD9;
	return output_ptr;
}
