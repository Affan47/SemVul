at2_send_messages(PrivAT2data *privdata)
{
    Msg *msg;

		if (privdata->modem->enable_mms &&
				gw_prioqueue_len(privdata->outgoing_queue) > 1)
            at2_send_modem_command(privdata, "AT+CMMS=2", 0, 0);

		if ((msg = gw_prioqueue_remove(privdata->outgoing_queue)))
				at2_send_one_message(privdata, msg);
}
