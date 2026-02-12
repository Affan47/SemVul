static int _annotate_may_store(annotate_state_t *state,
                               int is_shared,
                               const annotate_entrydesc_t *desc)
{
    unsigned int my_rights;
    unsigned int needed = 0;
    const char *acl = NULL;


    if (state->isadmin)
        return 1;

    if (state->which == ANNOTATION_SCOPE_SERVER) {


        return !is_shared;
    }
    else if (state->which == ANNOTATION_SCOPE_MAILBOX) {
        assert(state->mailbox);


        if (state->mbentry && state->mbentry->server)
            return 0;

        acl = state->mailbox->acl;


        needed = ACL_LOOKUP;
        if (is_shared)
            needed |= ACL_READ|ACL_WRITE|desc->extra_rights;

    }
    else if (state->which == ANNOTATION_SCOPE_MESSAGE) {
        assert(state->mailbox);
        acl = state->mailbox->acl;


        needed = (is_shared ? ACL_ANNOTATEMSG : ACL_READ);

    }

    if (!acl)
        return 0;

    my_rights = cyrus_acl_myrights(state->auth_state, acl);

    return ((my_rights & needed) == needed);
}
