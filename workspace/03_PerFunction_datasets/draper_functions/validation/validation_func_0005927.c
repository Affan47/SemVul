gdl_dock_paned_button_cb (GtkWidget      *widget,
                          GdkEventButton *event,
                          gpointer        user_data)
{
    GdlDockPaned *paned;

    g_return_val_if_fail (user_data != NULL && GDL_IS_DOCK_PANED (user_data), FALSE);

    paned = GDL_DOCK_PANED (user_data);
    if (event->button == 1) {
	if (event->type == GDK_BUTTON_PRESS) {

            GdlDockExpansionDirection expansion_direction;

            GDL_DOCK_ITEM_SET_FLAGS (user_data, GDL_DOCK_USER_ACTION);

            paned->in_drag = TRUE;

            g_object_get (GDL_DOCK_OBJECT (paned)->master,
                          "expand-direction", &expansion_direction,
                          NULL);

            switch (expansion_direction) {
            case GDL_DOCK_EXPANSION_DIRECTION_DOWN:
            {
                gint max_position, position;
                g_object_get (GDL_DOCK_ITEM (paned)->child,
                              "max-position", &max_position,
                              "position", &position,
                              NULL);

                paned->last_drag_position = position;


                if (position == max_position)
                    gdl_dock_paned_resize_paned_ancestors (paned, expansion_direction, 1);
                break;
            }
            default:
                ;
            }
        }
        else if (event->type == GDK_BUTTON_RELEASE) {
	     paned->last_drag_position = -1;
	     paned->in_drag = FALSE;
        }
        else {
            GDL_DOCK_ITEM_UNSET_FLAGS (user_data, GDL_DOCK_USER_ACTION);
            if (paned->position_changed) {

                if (GDL_DOCK_OBJECT (paned)->master)
                    g_signal_emit_by_name (GDL_DOCK_OBJECT (paned)->master, "layout-changed");
                paned->position_changed = FALSE;
            }
        }
    }

    return FALSE;
}
