sync_cookie_parse(char *cookie, PRBool *cookie_refresh, PRBool *allow_openldap_compat)
{
    char *p = NULL;
    char *q = NULL;
    Sync_Cookie *sc = NULL;


    if (cookie == NULL || *cookie == '\0') {
        *cookie_refresh = PR_TRUE;
        return NULL;
    }


    p = q = cookie;

    sc = (Sync_Cookie *)slapi_ch_calloc(1, sizeof(Sync_Cookie));
    if (strncmp(cookie, "rid=", 4) == 0) {
        if (*allow_openldap_compat != PR_TRUE) {
            slapi_log_err(SLAPI_LOG_ERR, SYNC_PLUGIN_SUBSYSTEM, "sync_cookie_parse - An openldap sync request was made, but " SYNC_ALLOW_OPENLDAP_COMPAT " is false\n");
            slapi_log_err(SLAPI_LOG_ERR, SYNC_PLUGIN_SUBSYSTEM, "sync_cookie_parse - To enable this run 'dsconf <instance> plugin contentsync set --allow-openldap on'\n");
            goto error_return;
        }


        sc->openldap_compat = PR_TRUE;
        p = strchr(q, ',');
        if (p == NULL) {

            *cookie_refresh = PR_TRUE;

            sc->cookie_client_signature = slapi_ch_strdup(q);

            sc->cookie_server_signature = NULL;
            sc->cookie_change_info = 0;
        } else {

            if (strncmp(p, ",csn=", 5) != 0) {

                goto error_return;
            }

            if (strlen(p) < 20) {

                goto error_return;
            }


            PR_ASSERT(p[0] == ',');
            p[0] = '\0';


            PR_ASSERT(p[19] == '.');
            p[19] = '\0';


            p = p + 5;
            PR_ASSERT(strlen(p) == 14);

            sc->cookie_client_signature = slapi_ch_strdup(q);
            sc->cookie_server_signature = NULL;

            sc->cookie_change_info = sync_olcsn2ulong(p);
            if (SYNC_INVALID_CHANGENUM == sc->cookie_change_info) {

                goto error_return;
            }

        }
    } else {


        p = strchr(q, '#');
        if (p) {
            *p = '\0';
            sc->cookie_server_signature = slapi_ch_strdup(q);
            q = p + 1;
            p = strchr(q, '#');
            if (p) {
                *p = '\0';
                sc->cookie_client_signature = slapi_ch_strdup(q);
                sc->cookie_change_info = sync_number2ulong(p + 1);
                if (SYNC_INVALID_CHANGENUM == sc->cookie_change_info) {
                    goto error_return;
                }
            } else {
                goto error_return;
            }
        }
    }
    return (sc);
error_return:
    slapi_ch_free_string(&(sc->cookie_client_signature));
    slapi_ch_free_string(&(sc->cookie_server_signature));
    slapi_ch_free((void **)&sc);
    return NULL;
}
