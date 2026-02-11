gnc_search_date_finalize (GObject *obj)
{
    GNCSearchDate *o;
    GNCSearchDatePrivate *priv;

    g_assert (IS_GNCSEARCH_DATE (obj));

    o = GNCSEARCH_DATE(obj);
    priv = _PRIVATE(o);
    if (priv->entry)
        gtk_widget_destroy (priv->entry);

    G_OBJECT_CLASS (parent_class)->finalize(obj);
}
