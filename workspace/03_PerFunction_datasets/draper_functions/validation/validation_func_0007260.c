gvc_level_bar_finalize (GObject *object)
{
        GvcLevelBar *bar;

        g_return_if_fail (object != NULL);
        g_return_if_fail (GVC_IS_LEVEL_BAR (object));

        bar = GVC_LEVEL_BAR (object);

        if (bar->priv->max_peak_id > 0) {
                g_source_remove (bar->priv->max_peak_id);
        }

        g_return_if_fail (bar->priv != NULL);

        G_OBJECT_CLASS (gvc_level_bar_parent_class)->finalize (object);
}
