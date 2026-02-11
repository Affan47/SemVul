httpsmsc_send(SMSCConn *conn, Msg *msg)
{
    ConnData *conndata = conn->data;
    Msg *sms = msg_duplicate(msg);
    double delay = 0;

    if (conn->throughput > 0) {
        delay = 1.0 / conn->throughput;
    }


    if (conndata->alt_charset &&
        charset_convert(sms->sms.msgdata, DEFAULT_CHARSET,
                        octstr_get_cstr(conndata->alt_charset)) != 0)
        error(0, "Failed to convert msgdata from charset <%s> to <%s>, will send as is.",
                 DEFAULT_CHARSET, octstr_get_cstr(conndata->alt_charset));

    conndata->open_sends++;
    conndata->send_sms(conn, sms);


    if (conn->throughput > 0)
        gwthread_sleep(delay);

    return 0;
}
