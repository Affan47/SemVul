image_rotate_simple (gpaint_image *image, int degrees)
{
	GdkPixbuf *newpixbuf;

	switch (degrees)
	{
        case GDK_PIXBUF_ROTATE_NONE:
        case GDK_PIXBUF_ROTATE_COUNTERCLOCKWISE:
        case GDK_PIXBUF_ROTATE_UPSIDEDOWN:
        case GDK_PIXBUF_ROTATE_CLOCKWISE:
            newpixbuf = gdk_pixbuf_rotate_simple (image->pixbuf, degrees);
            gdk_pixbuf_unref (image->pixbuf);
            image->pixbuf = newpixbuf;
            return 0;
            break;
        default:
            return 1;
    }
}
