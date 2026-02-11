oisd_submit_msg(SMSCConn *conn, Msg *msg)
{
    PrivData *pdata = conn->data;
    struct packet *packet;
    Octstr *ts = NULL;
    int ret;

    gw_assert(pdata != NULL);
    debug("bb.sms.oisd", 0, "OISD[%s]: sending message",
          octstr_get_cstr(conn->id));

    packet = packet_encode_message(msg, conn);
    if (!packet) {


        bb_smscconn_send_failed(conn, msg,
                SMSCCONN_FAILED_MALFORMED, octstr_create("MALFORMED"));
        return -1;
    }

    ret = oisd_request(packet, conn, &ts);
    if((ret == 0) && (ts) && DLR_IS_SUCCESS_OR_FAIL(msg->sms.dlr_mask) && !pdata->no_dlr) {
        dlr_add(conn->name, ts, msg);
    }
    octstr_destroy(ts);
    packet_destroy(packet);

    if (ret == -1) {
        bb_smscconn_send_failed(conn, msg,
                SMSCCONN_FAILED_REJECTED, octstr_create("REJECTED"));
    }
    else if (ret == -2) {
        oisd_close_socket(pdata);
        bb_smscconn_send_failed(conn, msg, SMSCCONN_FAILED_TEMPORARILY, NULL);
        mutex_lock(conn->flow_mutex);
        conn->status = SMSCCONN_DISCONNECTED;
        mutex_unlock(conn->flow_mutex);
    }
    else {
        bb_smscconn_sent(conn, msg, NULL);
    }

    return ret;
}
