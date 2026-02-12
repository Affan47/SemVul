sdap_get_ad_match_rule_initgroups_step(struct tevent_req *subreq)
{
    errno_t ret;
    struct tevent_req *req =
            tevent_req_callback_data(subreq, struct tevent_req);
    struct sdap_ad_match_rule_initgr_state *state =
            tevent_req_data(req, struct sdap_ad_match_rule_initgr_state);
    size_t count, i;
    struct sysdb_attrs **groups;
    char **sysdb_grouplist;

    ret = sdap_get_generic_recv(subreq, state, &count, &groups);
    talloc_zfree(subreq);
    if (ret != EOK) {
        DEBUG(SSSDBG_MINOR_FAILURE,
              "LDAP search failed: [%s]\n", sss_strerror(ret));
        goto error;
    }

    DEBUG(SSSDBG_TRACE_LIBS,
          "Search for users returned %zu results\n", count);


    if (count > 0) {
        state->groups = talloc_realloc(state, state->groups,
                                      struct sysdb_attrs *,
                                      state->count + count + 1);
        if (!state->groups) {
            tevent_req_error(req, ENOMEM);
            return;
        }


        for (i = 0; i < count; i++) {
            state->groups[state->count + i] =
                    talloc_steal(state->groups, groups[i]);
        }

        state->count += count;
        state->groups[state->count] = NULL;
    }


    state->base_iter++;
    if (state->search_bases[state->base_iter]) {

        ret = sdap_get_ad_match_rule_initgroups_next_base(req);
        if (ret != EOK) {
            goto error;
        }
        return;
    }


    if (state->count == 0) {
        DEBUG(SSSDBG_TRACE_LIBS,
              "User is not a member of any group in the search bases\n");
    }


    ret = get_sysdb_grouplist(state, state->sysdb, state->domain,
                              state->name, &sysdb_grouplist);
    if (ret != EOK) {
        DEBUG(SSSDBG_MINOR_FAILURE,
              "Could not get the list of groups for [%s] in the sysdb: "
               "[%s]\n",
               state->name, strerror(ret));
        goto error;
    }


    ret = sdap_initgr_common_store(state->sysdb,
                                   state->domain,
                                   state->opts,
                                   state->name,
                                   SYSDB_MEMBER_USER,
                                   sysdb_grouplist,
                                   state->groups,
                                   state->count);
    if (ret != EOK) {
        DEBUG(SSSDBG_MINOR_FAILURE,
              "Could not store groups for user [%s]: [%s]\n",
               state->name, strerror(ret));
        goto error;
    }

    tevent_req_done(req);
    return;

error:
    tevent_req_error(req, ret);
}
