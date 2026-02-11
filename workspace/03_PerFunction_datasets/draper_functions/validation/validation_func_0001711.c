fcgi_do_request(apr_pool_t *p, request_rec *r,
                           proxy_conn_rec *conn,
                           conn_rec *origin,
                           proxy_dir_conf *conf,
                           apr_uri_t *uri,
                           char *url, char *server_portstr)
{


    apr_uint16_t request_id = 1;
    apr_status_t rv;
    apr_pool_t *temp_pool;
    const char *err;


    rv = send_begin_request(conn, request_id);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01073)
                      "Failed Writing Request to %s:", server_portstr);
        conn->close = 1;
        return HTTP_SERVICE_UNAVAILABLE;
    }

    apr_pool_create(&temp_pool, r->pool);


    rv = send_environment(conn, r, temp_pool, request_id);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01074)
                      "Failed writing Environment to %s:", server_portstr);
        conn->close = 1;
        return HTTP_SERVICE_UNAVAILABLE;
    }


    rv = dispatch(conn, conf, r, temp_pool, request_id, &err);
    if (rv != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01075)
                      "Error dispatching request to %s: %s%s%s",
                      server_portstr,
                      err ? "(" : "",
                      err ? err : "",
                      err ? ")" : "");
        conn->close = 1;
        return HTTP_SERVICE_UNAVAILABLE;
    }

    return OK;
}
