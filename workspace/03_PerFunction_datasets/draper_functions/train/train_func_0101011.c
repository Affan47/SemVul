onexpose(GtkWidget *widget, GdkEventExpose *event, void *data)
{
    int x0 = event->area.x;
    int y0 = event->area.y;
    int w = event->area.width;
    int h = event->area.height;

    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x0 + w > gli_image_w) w = gli_image_w - x0;
    if (y0 + h > gli_image_h) h = gli_image_h - y0;
    if (w < 0) return;
    if (h < 0) return;

    if (!gli_drawselect)
        gli_windows_redraw();
    else
        gli_drawselect = FALSE;

    gdk_draw_rgb_image(canvas->window, canvas->style->black_gc,
        x0, y0, w, h,
        GDK_RGB_DITHER_NONE,
        gli_image_rgb + y0 * gli_image_s + x0 * 3,
        gli_image_s);
}
