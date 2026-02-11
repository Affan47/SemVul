generic_guid_end_handler(gpointer data_for_children,
                         GSList  *data_from_children, GSList *sibling_data,
                         gpointer parent_data, gpointer global_data,
                         gpointer *result, const gchar *tag)
{
    gchar *txt = NULL;
    GncGUID *gid;
    gboolean ok;

    txt = concatenate_child_result_chars(data_from_children);
    g_return_val_if_fail(txt, FALSE);

    gid = g_new(GncGUID, 1);
    if (!gid)
    {
        g_free(txt);
        return(FALSE);
    }

    ok = string_to_guid(txt, gid);
    g_free(txt);

    if (!ok)
    {
        PERR ("couldn't parse GncGUID");
        g_free(gid);
        return(FALSE);
    }

    *result = gid;
    return(TRUE);
}
