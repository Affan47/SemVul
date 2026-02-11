ario_dnd_tree_button_release_cb (GtkWidget *widget,
                                 GdkEventButton *event,
                                 ArioDndTree *dnd_tree)
{
        ARIO_LOG_FUNCTION_START;
        if (!dnd_tree->priv->dragging && !(event->state & GDK_CONTROL_MASK) && !(event->state & GDK_SHIFT_MASK)) {

                int bx, by;
                gtk_tree_view_convert_widget_to_bin_window_coords (GTK_TREE_VIEW (widget), event->x, event->y, &bx, &by);
                if (bx >= 0 && by >= 0) {

                        GtkTreePath *path;

                        gtk_tree_view_get_path_at_pos (GTK_TREE_VIEW (widget), event->x, event->y, &path, NULL, NULL, NULL);
                        if (path) {
                                GtkTreeSelection *selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (widget));
                                gtk_tree_selection_unselect_all (selection);
                                gtk_tree_selection_select_path (selection, path);
                                gtk_tree_path_free (path);
                        }
                }
        }

        dnd_tree->priv->dragging = FALSE;
        dnd_tree->priv->pressed = FALSE;

        return FALSE;
}
