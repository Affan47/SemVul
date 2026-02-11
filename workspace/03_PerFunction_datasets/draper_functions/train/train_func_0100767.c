bb_smscconn_sent(SMSCConn *conn, Msg *sms, Octstr *reply)
{
    if (sms->sms.split_parts != NULL) {
        handle_split(conn, sms, SMSCCONN_SUCCESS);
        octstr_destroy(reply);
        return;
    }

    counter_increase(outgoing_sms_counter);
    load_increase(outgoing_sms_load);
    if (conn) counter_increase(conn->sent);


    store_save_ack(sms, ack_success);

    bb_alog_sms(conn, sms, "Sent SMS");


    if (DLR_IS_SMSC_SUCCESS(sms->sms.dlr_mask)) {
        Msg *dlrmsg;

	if (reply == NULL)
	    reply = octstr_create("");

	octstr_insert_data(reply, 0, "ACK/", 4);
        dlrmsg = create_dlr_from_msg((conn->id?conn->id:conn->name), sms,
	                reply, DLR_SMSC_SUCCESS);
        if (dlrmsg != NULL) {
            bb_smscconn_receive(conn, dlrmsg);
        }
    }

    msg_destroy(sms);
    octstr_destroy(reply);
}
