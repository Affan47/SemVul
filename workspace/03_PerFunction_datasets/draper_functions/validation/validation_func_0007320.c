ini_comment_copy(struct ini_comment *ic,
                     struct ini_comment **ic_copy)
{
    int error = EOK;
    struct ref_array *ra = NULL;
    struct ini_comment *ic_new = NULL;

    TRACE_FLOW_ENTRY();

    error = ref_array_copy(ic->ra,
                           ini_comment_copy_cb,
                           ini_comment_cb,
                           NULL,
                           &ra);
    if (error) {
        TRACE_ERROR_NUMBER("Error creating a copy of ref array", error);
        return error;
    }

    ic_new = malloc(sizeof(struct ini_comment));
    if (!ic_new) {
        TRACE_ERROR_NUMBER("Memory allocation error", ENOMEM);
        ref_array_destroy(ra);
        return ENOMEM;
    }


    ic_new->ra = ra;
    ic_new->state = ic->state;

    *ic_copy = ic_new;

    TRACE_FLOW_EXIT();
    return error;
}
