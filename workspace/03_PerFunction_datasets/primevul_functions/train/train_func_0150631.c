gdPngErrorHandler (png_structp png_ptr, png_const_charp msg)
{
	jmpbuf_wrapper *jmpbuf_ptr;


	gd_error_ex(GD_ERROR, "gd-png: fatal libpng error: %s\n", msg);

	jmpbuf_ptr = png_get_error_ptr (png_ptr);
	if (jmpbuf_ptr == NULL) {
		gd_error_ex(GD_ERROR, "gd-png: EXTREMELY fatal error: jmpbuf unrecoverable; terminating.\n");
		exit (99);
	}

	longjmp (jmpbuf_ptr->jmpbuf, 1);
}
