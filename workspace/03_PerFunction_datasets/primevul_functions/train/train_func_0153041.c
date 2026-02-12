EXPORTED void list_auth_schemes(struct transaction_t *txn)
{
    struct auth_challenge_t *auth_chal = &txn->auth_chal;
    unsigned conn_close = (txn->flags.conn & CONN_CLOSE);
    struct auth_scheme_t *scheme;


    for (scheme = auth_schemes; scheme->name; scheme++) {
        if ((avail_auth_schemes & scheme->id) &&
            !(conn_close && (scheme->flags & AUTH_NEED_PERSIST))) {
            auth_chal->param = NULL;

            if (scheme->flags & AUTH_SERVER_FIRST) {

                http_auth(scheme->name, txn);

                if (!auth_chal->param) continue;
            }
            WWW_Authenticate(scheme->name, auth_chal->param);
        }
    }
}
