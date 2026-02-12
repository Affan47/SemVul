EXPORTED int annotate_state_fetch(annotate_state_t *state,
                         const strarray_t *entries, const strarray_t *attribs,
                         annotate_fetch_cb_t callback, void *rock)
{
    int i;
    struct glob *g;
    const ptrarray_t *non_db_entries;
    const annotate_entrydesc_t *db_entry;
    int r = 0;

    init_internal();

    annotate_state_start(state);
    state->callback = callback;
    state->callback_rock = rock;


    for (i = 0 ; i < attribs->count ; i++)
    {
        const char *s = attribs->data[i];
        int attribcount;


        g = glob_init(s, '.');

        for (attribcount = 0;
             annotation_attributes[attribcount].name;
             attribcount++) {
            if (GLOB_MATCH(g, annotation_attributes[attribcount].name)) {
                if (annotation_attributes[attribcount].entry & ATTRIB_DEPRECATED) {
                    if (strcmp(s, "*"))
                        syslog(LOG_WARNING, "annotatemore_fetch: client used "
                                            "deprecated attribute \"%s\", ignoring",
                                            annotation_attributes[attribcount].name);
                }
                else
                    state->attribs |= annotation_attributes[attribcount].entry;
            }
        }

        glob_free(&g);
    }

    if (!state->attribs)
        goto out;

    if (state->which == ANNOTATION_SCOPE_SERVER) {
        non_db_entries = &server_entries;
        db_entry = &server_db_entry;
    }
    else if (state->which == ANNOTATION_SCOPE_MAILBOX) {
        non_db_entries = &mailbox_entries;
        db_entry = &mailbox_db_entry;
    }
    else if (state->which == ANNOTATION_SCOPE_MESSAGE) {
        non_db_entries = &message_entries;
        db_entry = &message_db_entry;
    }
    else {
        syslog(LOG_ERR, "IOERROR: unknown annotation scope %d", state->which);
        r = IMAP_INTERNAL;
        goto out;
    }


    for (i = 0 ; i < entries->count ; i++)
    {
        const char *s = entries->data[i];
        int j;
        int check_db = 0;

        g = glob_init(s, '/');

        for (j = 0 ; j < non_db_entries->count ; j++) {
            const annotate_entrydesc_t *desc = non_db_entries->data[j];

            if (!desc->get)
                continue;

            if (GLOB_MATCH(g, desc->name)) {


                if ((desc->proxytype != PROXY_ONLY)
                    || proxy_fetch_func)
                    _annotate_state_add_entry(state, desc, desc->name);
            }

            if (!strcmp(s, desc->name)) {

                if (desc->proxytype != PROXY_ONLY) {
                    state->orig_entry = entries;
                }
                break;
            }
        }

        if (j == non_db_entries->count) {

            state->orig_entry = entries;
            check_db = 1;
        }


        if (check_db &&
            ((db_entry->proxytype != PROXY_ONLY) || proxy_fetch_func)) {

            _annotate_state_add_entry(state, db_entry, s);
        }

        glob_free(&g);
    }

    if (state->which == ANNOTATION_SCOPE_SERVER) {
        _annotate_fetch_entries(state, 1);
    }
    else if (state->which == ANNOTATION_SCOPE_MAILBOX) {

        if (state->entry_list || proxy_fetch_func) {
            if (proxy_fetch_func) {
                r = annotate_state_need_mbentry(state);
                if (r)
                    goto out;
                assert(state->mbentry);
            }

            if (proxy_fetch_func && state->orig_entry) {
                state->orig_mailbox = state->mbentry->name;
                state->orig_attribute = attribs;
            }

            _annotate_fetch_entries(state, 1);

            if (proxy_fetch_func && state->orig_entry && state->mbentry->server &&
                !hash_lookup(state->mbentry->server, &state->server_table)) {

                proxy_fetch_func(state->mbentry->server, state->mbentry->ext_name,
                                 state->orig_entry, state->orig_attribute);
                hash_insert(state->mbentry->server, (void *)0xDEADBEEF, &state->server_table);
            }
        }
    }
    else if (state->which == ANNOTATION_SCOPE_MESSAGE) {
        _annotate_fetch_entries(state, 0);
    }


    flush_entryatt(state);

out:
    annotate_state_finish(state);
    return r;
}
