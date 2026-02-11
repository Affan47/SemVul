gerror_error_func (png_structp     png_ptr,
		   png_const_charp message)
{
	GError ***error_p = png_get_error_ptr (png_ptr);
	GError  **error = *error_p;

	if (error != NULL)
		*error = g_error_new (G_IO_ERROR, G_IO_ERROR_INVALID_DATA, "%s", message);
}
