STATIC void
S_delete_recursion_entry(pTHX_ void *key)
{


    dVAR;
    SV ** current_entry;
    const STRLEN key_len = strlen((const char *) key);
    DECLARATION_FOR_GLOBAL_CONTEXT;

    SWITCH_TO_GLOBAL_CONTEXT;


    current_entry = hv_fetch(PL_user_def_props, (const char *) key, key_len, 0);
    if (     current_entry
        && ! is_invlist(*current_entry)
        && ! SvPOK(*current_entry))
    {
        (void) hv_delete(PL_user_def_props, (const char *) key, key_len,
                                                                    G_DISCARD);
    }

    RESTORE_CONTEXT;
}
