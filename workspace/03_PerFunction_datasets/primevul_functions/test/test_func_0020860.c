static void annotation_get_fromdb(annotate_state_t *state,
                                  struct annotate_entry_list *entry)
{
    const char *mboxname = (state->mailbox ? state->mailbox->name : "");
    state->found = 0;

    annotatemore_findall(mboxname, state->uid, entry->name, 0, &rw_cb, state, 0);

    if (state->found != state->attribs &&
        (!strchr(entry->name, '%') && !strchr(entry->name, '*'))) {


        struct buf empty = BUF_INITIALIZER;
        if (!(state->found & (ATTRIB_VALUE_PRIV|ATTRIB_SIZE_PRIV)) &&
            (state->attribs & (ATTRIB_VALUE_PRIV|ATTRIB_SIZE_PRIV))) {

            output_entryatt(state, entry->name, state->userid, &empty);
        }
        if (!(state->found & (ATTRIB_VALUE_SHARED|ATTRIB_SIZE_SHARED)) &&
            (state->attribs & (ATTRIB_VALUE_SHARED|ATTRIB_SIZE_SHARED))) {

            output_entryatt(state, entry->name, "", &empty);
        }

        flush_entryatt(state);
    }
}
