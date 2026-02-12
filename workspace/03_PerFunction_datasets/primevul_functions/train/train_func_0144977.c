gdk_pixbuf__jpeg_image_stop_load (gpointer data, GError **error)
{
	JpegProgContext *context = (JpegProgContext *) data;
        gboolean retval;

	g_return_val_if_fail (context != NULL, TRUE);


	if (context->pixbuf)
		g_object_unref (context->pixbuf);


	context->jerr.error = error;
	if (sigsetjmp (context->jerr.setjmp_buffer, 1)) {
                retval = FALSE;
	} else {
		jpeg_finish_decompress (&context->cinfo);
                retval = TRUE;
	}

        jpeg_destroy_decompress (&context->cinfo);

	if (context->cinfo.src) {
		my_src_ptr src = (my_src_ptr) context->cinfo.src;

		g_free (src);
	}

	g_free (context);

        return retval;
}
