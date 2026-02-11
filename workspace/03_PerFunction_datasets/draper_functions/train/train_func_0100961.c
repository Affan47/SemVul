smsdvb_onresponse(void *context, struct smscore_buffer_t *cb)
{
	struct smsdvb_client_t *client = (struct smsdvb_client_t *) context;
	struct sms_msg_hdr *phdr = (struct sms_msg_hdr *) (((u8 *) cb->p)
			+ cb->offset);
	void *p = phdr + 1;
	struct dvb_frontend *fe = &client->frontend;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	bool is_status_update = false;

	switch (phdr->msg_type) {
	case MSG_SMS_DVBT_BDA_DATA:


		if (client->feed_users && client->has_tuned)
			dvb_dmx_swfilter(&client->demux, p,
					 cb->size - sizeof(struct sms_msg_hdr));
		break;

	case MSG_SMS_RF_TUNE_RES:
	case MSG_SMS_ISDBT_TUNE_RES:
		complete(&client->tune_done);
		break;

	case MSG_SMS_SIGNAL_DETECTED_IND:
		client->fe_status = FE_HAS_SIGNAL  | FE_HAS_CARRIER |
				    FE_HAS_VITERBI | FE_HAS_SYNC    |
				    FE_HAS_LOCK;

		is_status_update = true;
		break;

	case MSG_SMS_NO_SIGNAL_IND:
		client->fe_status = 0;

		is_status_update = true;
		break;

	case MSG_SMS_TRANSMISSION_IND:
		smsdvb_update_tx_params(client, p);

		is_status_update = true;
		break;

	case MSG_SMS_HO_PER_SLICES_IND:
		smsdvb_update_per_slices(client, p);

		is_status_update = true;
		break;

	case MSG_SMS_GET_STATISTICS_RES:
		switch (smscore_get_device_mode(client->coredev)) {
		case DEVICE_MODE_ISDBT:
		case DEVICE_MODE_ISDBT_BDA:
			smsdvb_update_isdbt_stats(client, p);
			break;
		default:

			smsdvb_update_dvb_stats(client, p + sizeof(u32));
		}

		is_status_update = true;
		break;


	case MSG_SMS_GET_STATISTICS_EX_RES:

		smsdvb_update_isdbt_stats_ex(client, p + sizeof(u32));
		is_status_update = true;
		break;
	default:
		pr_debug("message not handled\n");
	}
	smscore_putbuffer(client->coredev, cb);

	if (is_status_update) {
		if (client->fe_status & FE_HAS_LOCK) {
			sms_board_dvb3_event(client, DVB3_EVENT_FE_LOCK);
			if (client->last_per == c->block_error.stat[0].uvalue)
				sms_board_dvb3_event(client, DVB3_EVENT_UNC_OK);
			else
				sms_board_dvb3_event(client, DVB3_EVENT_UNC_ERR);
			client->has_tuned = true;
		} else {
			smsdvb_stats_not_ready(fe);
			client->has_tuned = false;
			sms_board_dvb3_event(client, DVB3_EVENT_FE_UNLOCK);
		}
		complete(&client->stats_done);
	}

	return 0;
}
