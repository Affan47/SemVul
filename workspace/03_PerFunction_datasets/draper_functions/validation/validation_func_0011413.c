ensure_font_list (FontViewModel *self)
{
    FcPattern *pat;
    FcObjectSet *os;


    if (!FcInitReinitialize())
        return;

    if (self->priv->cancellable) {
        g_cancellable_cancel (self->priv->cancellable);
        g_clear_object (&self->priv->cancellable);
    }

    gtk_list_store_clear (GTK_LIST_STORE (self));

    pat = FcPatternCreate ();
    os = FcObjectSetBuild (FC_FILE, FC_FAMILY, FC_WEIGHT, FC_SLANT, NULL);

    g_mutex_lock (&self->priv->font_list_mutex);

    if (self->priv->font_list) {
        FcFontSetDestroy (self->priv->font_list);
        self->priv->font_list = NULL;
    }

    self->priv->font_list = FcFontList (NULL, pat, os);

    g_mutex_unlock (&self->priv->font_list_mutex);

    FcPatternDestroy (pat);
    FcObjectSetDestroy (os);

    if (!self->priv->font_list)
        return;

    self->priv->cancellable = g_cancellable_new ();
    g_io_scheduler_push_job (load_font_infos, self, NULL,
                             G_PRIORITY_DEFAULT, self->priv->cancellable);
}
