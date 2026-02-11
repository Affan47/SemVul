check_ref_count(GObject *object,
                GQuark key,
                GSList *stack,
                GSList **errors)
{
    gchar *s;

    if (!object || object->ref_count == 1)
        return TRUE;

    s = format_stack(object, stack);
    *errors = g_slist_prepend(*errors,
                              FAIL(GWY_DATA_ERROR_REF_COUNT, key,
                                   _("ref_count is %d for %s"),
                                   object->ref_count, s));
    g_free(s);

    return FALSE;
}
