um_crop_area_set_picture (UmCropArea *area,
                          GdkPixbuf  *pixbuf)
{
        gint width;
        gint height;

        if (area->priv->browse_pixbuf) {
                g_object_unref (area->priv->browse_pixbuf);
                area->priv->browse_pixbuf = NULL;
        }
        if (pixbuf) {
                area->priv->browse_pixbuf = g_object_ref (pixbuf);
                width = gdk_pixbuf_get_width (pixbuf);
                height = gdk_pixbuf_get_height (pixbuf);
        } else {
                width = 0;
                height = 0;
        }

        area->priv->crop.width = 2 * area->priv->base_width;
        area->priv->crop.height = 2 * area->priv->base_height;
        area->priv->crop.x = (width - area->priv->crop.width) / 2;
        area->priv->crop.y = (height - area->priv->crop.height) / 2;

        area->priv->scale = 0.0;
        area->priv->image.x = 0;
        area->priv->image.y = 0;
        area->priv->image.width = 0;
        area->priv->image.height = 0;

        gtk_widget_queue_draw (GTK_WIDGET (area));
}
