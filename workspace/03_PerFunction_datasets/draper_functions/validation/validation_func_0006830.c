generic_parse_reply(SMSCConn *conn, Msg *msg, int status,
                                List *headers, Octstr *body)
{
    ConnData *conndata = conn->data;
    size_t n_match = 1;
    regmatch_t p_match[10];


    if ((conndata->success_regex != NULL) &&
        (gw_regex_exec(conndata->success_regex, body, n_match, p_match, 0) == 0)) {
        bb_smscconn_sent(conn, msg, NULL);
    }
    else if ((conndata->permfail_regex != NULL) &&
        (gw_regex_exec(conndata->permfail_regex, body, n_match, p_match, 0) == 0)) {
        error(0, "HTTP[%s]: Message not accepted.", octstr_get_cstr(conn->id));
        bb_smscconn_send_failed(conn, msg,
            SMSCCONN_FAILED_MALFORMED, octstr_duplicate(body));
    }
    else if ((conndata->tempfail_regex != NULL) &&
        (gw_regex_exec(conndata->tempfail_regex, body, n_match, p_match, 0) == 0)) {
        warning(0, "HTTP[%s]: Message temporary not accepted, will retry.",
                octstr_get_cstr(conn->id));
        bb_smscconn_send_failed(conn, msg,
            SMSCCONN_FAILED_TEMPORARILY, octstr_duplicate(body));
    }
    else {
        error(0, "HTTP[%s]: Message was rejected. SMSC reponse was:",
              octstr_get_cstr(conn->id));
        octstr_dump(body, 0);
        bb_smscconn_send_failed(conn, msg,
            SMSCCONN_FAILED_REJECTED, octstr_create("REJECTED"));
    }
}
