attempt_to_dock_on_host (GdlDockPlaceholder *ph, GdlDockObject *host,
                         GdlDockObject *requestor, GdlDockPlacement placement,
                         gpointer other_data)
{
    GdlDockObject *parent;
    GtkAllocation  allocation;
    gint host_width;
    gint host_height;

    gtk_widget_get_allocation (GTK_WIDGET (host), &allocation);
    host_width = allocation.width;
    host_height = allocation.height;

    if (placement != GDL_DOCK_CENTER || !GDL_IS_DOCK_PANED (host)) {

        gdl_dock_object_dock (host, requestor,
                              placement, other_data);
    } else {


        GtkWidget *biggest_child = NULL;
        gint biggest_child_area = 0;

        find_biggest_dock_item (GTK_CONTAINER (host), &biggest_child,
                                &biggest_child_area);

        if (biggest_child) {

            gdl_dock_object_dock (GDL_DOCK_OBJECT (biggest_child), requestor,
                                  placement, other_data);
        } else {
            g_warning ("No suitable child found! Should not be here!");

            gdl_dock_object_dock (GDL_DOCK_OBJECT (host), requestor,
                                  placement, other_data);
        }
    }

    parent = gdl_dock_object_get_parent_object (requestor);


    switch (placement) {
        case GDL_DOCK_LEFT:
            if (ph->priv->width > 0) {
                g_object_set (G_OBJECT (parent), "position",
                              ph->priv->width, NULL);
            }
            break;
        case GDL_DOCK_RIGHT:
            if (ph->priv->width > 0) {
                gint complementary_width = host_width - ph->priv->width;

                if (complementary_width > 0)
                    g_object_set (G_OBJECT (parent), "position",
                                  complementary_width, NULL);
            }
            break;
        case GDL_DOCK_TOP:
            if (ph->priv->height > 0) {
                g_object_set (G_OBJECT (parent), "position",
                              ph->priv->height, NULL);
            }
            break;
        case GDL_DOCK_BOTTOM:
            if (ph->priv->height > 0) {
                gint complementary_height = host_height - ph->priv->height;

                if (complementary_height > 0)
                    g_object_set (G_OBJECT (parent), "position",
                                  complementary_height, NULL);
            }
            break;
        default:

            break;
    }
}
