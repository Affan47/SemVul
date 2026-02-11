evas_software_xlib_x_write_mask_line(Outbuf *buf, X_Output_Buffer *xob, DATA32 *src, int w, int y)
{
   int x;
   DATA32 *src_ptr;
   DATA8 *dst_ptr;
   int bpl = 0;

   src_ptr = src;
   dst_ptr = evas_software_xlib_x_output_buffer_data(xob, &bpl);
   dst_ptr = dst_ptr + (bpl * y);
   w -= 7;
   if (buf->priv.x11.xlib.bit_swap)
     {
	for (x = 0; x < w; x += 8)
	  {
	     *dst_ptr =
	       ((A_VAL(&(src_ptr[0])) >> 7) << 7) |
	       ((A_VAL(&(src_ptr[1])) >> 7) << 6) |
	       ((A_VAL(&(src_ptr[2])) >> 7) << 5) |
	       ((A_VAL(&(src_ptr[3])) >> 7) << 4) |
	       ((A_VAL(&(src_ptr[4])) >> 7) << 3) |
	       ((A_VAL(&(src_ptr[5])) >> 7) << 2) |
	       ((A_VAL(&(src_ptr[6])) >> 7) << 1) |
	       ((A_VAL(&(src_ptr[7])) >> 7) << 0);
	     src_ptr += 8;
	     dst_ptr++;
	  }
     }
   else
     {
	for (x = 0; x < w; x += 8)
	  {
	     *dst_ptr =
	       ((A_VAL(&(src_ptr[0])) >> 7) << 0) |
	       ((A_VAL(&(src_ptr[1])) >> 7) << 1) |
	       ((A_VAL(&(src_ptr[2])) >> 7) << 2) |
	       ((A_VAL(&(src_ptr[3])) >> 7) << 3) |
	       ((A_VAL(&(src_ptr[4])) >> 7) << 4) |
	       ((A_VAL(&(src_ptr[5])) >> 7) << 5) |
	       ((A_VAL(&(src_ptr[6])) >> 7) << 6) |
	       ((A_VAL(&(src_ptr[7])) >> 7) << 7);
	     src_ptr += 8;
	     dst_ptr++;
	  }
     }
   w += 7;
   for (; x < w; x ++)
     {
	XPutPixel(xob->xim, x, y, A_VAL(src_ptr) >> 7);
	src_ptr++;
     }
}
