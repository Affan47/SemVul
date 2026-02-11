_rsvg_handle_allow_load (RsvgHandle *handle,
                         const char *uri,
                         GError **error)
{
    RsvgHandlePrivate *priv = handle->priv;
    GFile *base;
    char *path, *dir;
    char *scheme = NULL, *cpath = NULL, *cdir = NULL;

    g_assert (handle->priv->load_policy == RSVG_LOAD_POLICY_STRICT);

    scheme = g_uri_parse_scheme (uri);


    if (scheme == NULL)
        goto deny;


    if (g_str_equal (scheme, "data"))
        goto allow;


    if (priv->base_gfile == NULL)
        goto deny;


    if (!g_file_has_uri_scheme (priv->base_gfile, scheme))
        goto deny;


    if (g_str_equal (scheme, "resource"))
        goto allow;


    if (!g_str_equal (scheme, "file"))
        goto deny;

    base = g_file_get_parent (priv->base_gfile);
    if (base == NULL)
        goto deny;

    dir = g_file_get_path (base);
    g_object_unref (base);

    cdir = realpath (dir, NULL);
    g_free (dir);
    if (cdir == NULL)
        goto deny;

    path = g_filename_from_uri (uri, NULL, NULL);
    if (path == NULL)
        goto deny;

    cpath = realpath (path, NULL);
    g_free (path);

    if (cpath == NULL)
        goto deny;


    if (!g_str_has_prefix (cpath, cdir) ||
        cpath[strlen (cdir)] != G_DIR_SEPARATOR)
        goto deny;


 allow:
    g_free (scheme);
    free (cpath);
    free (cdir);
    return TRUE;

 deny:
    g_free (scheme);
    free (cpath);
    free (cdir);

    g_set_error (error, G_IO_ERROR, G_IO_ERROR_PERMISSION_DENIED,
                 "File may not link to URI \"%s\"", uri);
    return FALSE;
}
