static int _annotate_may_fetch(annotate_state_t *state,
                               const annotate_entrydesc_t *desc)
{
    unsigned int my_rights;
    unsigned int needed = 0;
    const char *acl = NULL;


    if (state->isadmin)
        return 1;


    if ((desc->type & ATTRIB_NO_FETCH_ACL_CHECK))
        return 1;

    if (state->which == ANNOTATION_SCOPE_SERVER) {


        return 1;
    }
    else if (state->which == ANNOTATION_SCOPE_MAILBOX) {
        assert(state->mailbox || state->mbentry);


        if (state->mbentry && state->mbentry->server)
            return 0;

        if (state->mailbox) acl = state->mailbox->acl;
        else if (state->mbentry) acl = state->mbentry->acl;


        needed = ACL_LOOKUP|ACL_READ;

    }
    else if (state->which == ANNOTATION_SCOPE_MESSAGE) {
        assert(state->mailbox);
        acl = state->mailbox->acl;


        needed = ACL_READ;

    }

    if (!acl)
        return 0;

    my_rights = cyrus_acl_myrights(state->auth_state, acl);

    return ((my_rights & needed) == needed);
}
