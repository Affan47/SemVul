gnome_bg_create_frame_thumbnail (GnomeBG			*bg,
				 GnomeDesktopThumbnailFactory	*factory,
				 GdkScreen			*screen,
				 int				 dest_width,
				 int				 dest_height,
				 int				 frame_num)
{
	GnomeBGSlideShow *show;
	GdkPixbuf *result;
	GdkPixbuf *thumb;
        GList *l;
        int skipped;
        gboolean is_fixed;

	g_return_val_if_fail (bg != NULL, FALSE);

	show = get_as_slideshow (bg, bg->filename);

	if (!show)
		return NULL;


	if (frame_num < 0 || frame_num >= gnome_bg_slide_show_get_num_slides (show))
		return NULL;


        gnome_bg_slide_show_get_slide (show, frame_num, dest_width, dest_height, NULL, NULL, &is_fixed, NULL, NULL);

	skipped = 0;
        while (!is_fixed) {
            skipped++;
            gnome_bg_slide_show_get_slide (show, frame_num, dest_width, dest_height, NULL, NULL, &is_fixed, NULL, NULL);
        }

	result = gdk_pixbuf_new (GDK_COLORSPACE_RGB, FALSE, 8, dest_width, dest_height);

	draw_color (bg, result);

	if (bg->placement != G_DESKTOP_BACKGROUND_STYLE_NONE) {
		thumb = create_img_thumbnail (bg, factory, screen, dest_width, dest_height, frame_num + skipped);

		if (thumb) {
			draw_image_for_thumb (bg, thumb, result);
			g_object_unref (thumb);
		}
	}

	return result;
}
