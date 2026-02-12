png_reset_crc(png_structrp png_ptr)
{

   png_ptr->crc = (png_uint_32)crc32(0, Z_NULL, 0);
}
