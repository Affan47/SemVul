gdl_dock_layout_load_from_file (GdlDockLayout *layout,
                                const gchar   *filename)
{
    gboolean retval = FALSE;

    if (layout->priv->doc) {
        xmlFreeDoc (layout->priv->doc);
        layout->priv->doc = NULL;
        layout->priv->dirty = FALSE;
        g_object_notify (G_OBJECT (layout), "dirty");
    }


    if (g_file_test (filename, G_FILE_TEST_IS_REGULAR)) {
        layout->priv->doc = xmlParseFile (filename);
        if (layout->priv->doc) {
            xmlNodePtr root = layout->priv->doc->children;

            if (root && !strcmp ((char*)root->name, ROOT_ELEMENT)) {
                retval = TRUE;
            } else {
                xmlFreeDoc (layout->priv->doc);
                layout->priv->doc = NULL;
            }
        }
    }

    return retval;
}
