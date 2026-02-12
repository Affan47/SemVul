static void krb5_resolve_kpasswd_done(struct tevent_req *subreq)
{
    struct tevent_req *req = tevent_req_callback_data(subreq, struct tevent_req);
    struct krb5_auth_state *state = tevent_req_data(req, struct krb5_auth_state);
    int ret;

    ret = be_resolve_server_recv(subreq, &state->kr->kpasswd_srv);
    talloc_zfree(subreq);
    if (ret) {


        state->pam_status = PAM_AUTHTOK_LOCK_BUSY;
        state->dp_err = DP_ERR_OK;
        tevent_req_done(req);
        return;
    }

    krb5_find_ccache_step(req);
}
