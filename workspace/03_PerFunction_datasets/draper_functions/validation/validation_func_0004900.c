gdl_dock_placeholder_add (GtkContainer *container,
                          GtkWidget    *widget)
{
    GdlDockPlaceholder *ph;
    GdlDockPlacement    pos = GDL_DOCK_CENTER;

    g_return_if_fail (GDL_IS_DOCK_PLACEHOLDER (container));
    g_return_if_fail (GDL_IS_DOCK_ITEM (widget));

    ph = GDL_DOCK_PLACEHOLDER (container);
    if (ph->priv->placement_stack)
        pos = (GdlDockPlacement) ph->priv->placement_stack->data;

    gdl_dock_object_dock (GDL_DOCK_OBJECT (ph), GDL_DOCK_OBJECT (widget),
                          pos, NULL);
}
