static apr_status_t session_output_filter(ap_filter_t * f,
        apr_bucket_brigade * in)
{


    request_rec *r = f->r->main;
    if (!r) {
        r = f->r;
    }
    while (r) {
        session_rec *z = NULL;
        session_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                      &session_module);


        ap_session_load(r, &z);
        if (!z || z->written) {
            r = r->next;
            continue;
        }


        if (conf->header_set) {
            const char *override = apr_table_get(r->err_headers_out, conf->header);
            if (!override) {
                override = apr_table_get(r->headers_out, conf->header);
            }
            if (override) {
                apr_table_unset(r->err_headers_out, conf->header);
                apr_table_unset(r->headers_out, conf->header);
                z->encoded = override;
                z->dirty = 1;
                session_identity_decode(r, z);
            }
        }


        ap_session_save(r, z);

        r = r->next;
    }


    ap_remove_output_filter(f);


    return ap_pass_brigade(f->next, in);

}
