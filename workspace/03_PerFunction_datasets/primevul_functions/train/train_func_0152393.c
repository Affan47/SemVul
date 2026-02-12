sdap_get_ad_match_rule_initgroups_send(TALLOC_CTX *mem_ctx,
                                       struct tevent_context *ev,
                                       struct sdap_options *opts,
                                       struct sysdb_ctx *sysdb,
                                       struct sss_domain_info *domain,
                                       struct sdap_handle *sh,
                                       const char *name,
                                       const char *orig_dn,
                                       int timeout)
{
    errno_t ret;
    struct tevent_req *req;
    struct sdap_ad_match_rule_initgr_state *state;
    const char **filter_members;
    char *sanitized_user_dn;

    req = tevent_req_create(mem_ctx, &state,
                            struct sdap_ad_match_rule_initgr_state);
    if (!req) return NULL;

    state->ev = ev;
    state->opts = opts;
    state->sysdb = sysdb;
    state->domain = domain;
    state->sh = sh;
    state->name = name;
    state->orig_dn = orig_dn;
    state->base_iter = 0;
    state->search_bases = opts->sdom->group_search_bases;


    filter_members = talloc_array(state, const char *, 2);
    if (!filter_members) {
        ret = ENOMEM;
        goto immediate;
    }
    filter_members[0] = opts->group_map[SDAP_AT_GROUP_MEMBER].name;
    filter_members[1] = NULL;

    ret = build_attrs_from_map(state, opts->group_map,
                               SDAP_OPTS_GROUP,
                               filter_members,
                               &state->attrs, NULL);
    if (ret != EOK) {
        DEBUG(SSSDBG_MINOR_FAILURE,
              "Could not build attribute map: [%s]\n",
               strerror(ret));
        goto immediate;
    }


    ret = sss_filter_sanitize(state, state->orig_dn, &sanitized_user_dn);
    if (ret != EOK) {
        DEBUG(SSSDBG_MINOR_FAILURE,
              "Could not sanitize user DN: %s\n",
               strerror(ret));
        goto immediate;
    }


    state->base_filter =
            talloc_asprintf(state,
                            "(&(%s:%s:=%s)(objectClass=%s))",
                            state->opts->group_map[SDAP_AT_GROUP_MEMBER].name,
                            SDAP_MATCHING_RULE_IN_CHAIN,
                            sanitized_user_dn,
                            state->opts->group_map[SDAP_OC_GROUP].name);
    talloc_zfree(sanitized_user_dn);
    if (!state->base_filter) {
        ret = ENOMEM;
        goto immediate;
    }


    ret = sdap_get_ad_match_rule_initgroups_next_base(req);
    if (ret != EOK) {
        DEBUG(SSSDBG_MINOR_FAILURE,
              "sdap_get_ad_match_rule_members_next_base failed: [%s]\n",
               strerror(ret));
        goto immediate;
    }

    return req;

immediate:
    tevent_req_error(req, ret);
    tevent_req_post(req, ev);
    return req;
}
