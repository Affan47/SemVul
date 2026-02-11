rtp_sl_packet_cbk(void *udta, char *payload, u32 size, GF_SLHeader *hdr, GF_Err e)
{
	RTPStream *ch = (RTPStream *)udta;

	if (ch->rtp_ch->packet_loss) e = GF_REMOTE_SERVICE_ERROR;

	if (ch->owner->first_packet_drop && (hdr->packetSequenceNumber >= ch->owner->first_packet_drop) ) {
		if ( (hdr->packetSequenceNumber - ch->owner->first_packet_drop) % ch->owner->frequency_drop)
			gf_term_on_sl_packet(ch->owner->service, ch->channel, payload, size, hdr, e);
	} else {
		gf_term_on_sl_packet(ch->owner->service, ch->channel, payload, size, hdr, e);
	}
}
