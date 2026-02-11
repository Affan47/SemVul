button_release_event_cb (glView            *view,
                         GdkEventButton    *event)
{
        gboolean     return_value = FALSE;
        GdkWindow   *bin_window;
        GdkWindow   *window;
	cairo_t     *cr;
        gdouble      scale;
        gdouble      x, y;
        GdkCursor   *cursor;

        bin_window = gtk_layout_get_bin_window (GTK_LAYOUT (view->canvas));
        window = gtk_widget_get_window (view->canvas);

	cr = gdk_cairo_create (bin_window);


        scale = view->zoom * view->home_scale;
        cairo_scale (cr, scale, scale);
        cairo_translate (cr, view->x0, view->y0);

        x = event->x;
        y = event->y;
        cairo_device_to_user (cr, &x, &y);

        switch (event->button)
        {

        case 1:
                view->grabbed_flag = FALSE;
                gdk_pointer_ungrab (event->time);


                switch (view->mode)
                {
                case GL_VIEW_MODE_ARROW:
                        switch (view->state)
                        {
                        case GL_VIEW_ARROW_RESIZE:
                                view->resize_object = NULL;

                                view->state = GL_VIEW_IDLE;
                                break;

                        case GL_VIEW_ARROW_SELECT_REGION:
#ifdef CLIP_UPDATES
                                gl_view_update_region (view, cr, &view->select_region);
#else
                                gl_view_update (view);
#endif

                                view->select_region_visible = FALSE;
                                view->select_region.x2 = x;
                                view->select_region.y2 = y;

                                gl_label_select_region (view->label, &view->select_region);

                                view->state = GL_VIEW_IDLE;
                                break;

                        default:
                                view->state = GL_VIEW_IDLE;
                                break;

                        }

                        return_value = TRUE;
                        break;


                case GL_VIEW_MODE_OBJECT_CREATE:
                        switch (view->create_type)
                        {
                        case GL_LABEL_OBJECT_BOX:
                                gl_view_box_create_button_release_event (view, x, y);
                                break;
                        case GL_LABEL_OBJECT_ELLIPSE:
                                gl_view_ellipse_create_button_release_event (view, x, y);
                                break;
                        case GL_LABEL_OBJECT_LINE:
                                gl_view_line_create_button_release_event (view, x, y);
                                break;
                        case GL_LABEL_OBJECT_IMAGE:
                                gl_view_image_create_button_release_event (view, x, y);
                                break;
                        case GL_LABEL_OBJECT_TEXT:
                                gl_view_text_create_button_release_event (view, x, y);
                                break;
                        case GL_LABEL_OBJECT_BARCODE:
                                gl_view_barcode_create_button_release_event (view, x, y);
                                break;
                        default:
                                g_message ("Invalid create type.");
                        }
                        view->mode = GL_VIEW_MODE_ARROW;
                        view->state = GL_VIEW_IDLE;
                        cursor = gdk_cursor_new (GDK_LEFT_PTR);
                        gdk_window_set_cursor (window, cursor);
                        gdk_cursor_unref (cursor);

                        gl_label_select_object (view->label, view->create_object);
                        break;


                default:
                        g_message ("Invalid view mode.");
                }

        }

	cairo_destroy (cr);

        return return_value;
}
