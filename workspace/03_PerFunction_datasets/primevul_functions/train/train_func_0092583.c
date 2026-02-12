idprime_compute_signature(struct sc_card *card,
	const u8 * data, size_t datalen, u8 * out, size_t outlen)
{
	int r;
	struct sc_apdu apdu;
	u8 *p;
	u8 sbuf[128];
	u8 rbuf[4096];
	size_t rbuflen = sizeof(rbuf);

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);


	if (datalen + 2 > sizeof(sbuf)) {
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INTERNAL);
	}

	p = sbuf;
	*(p++) = 0x90;
	*(p++) = datalen;
	memcpy(p, data, datalen);
	p += datalen;


	sc_format_apdu(card, &apdu, SC_APDU_CASE_4, 0x2A, 0x90, 0xA0);
	apdu.resp = rbuf;
	apdu.resplen = rbuflen;
	apdu.le = datalen;

	apdu.data = sbuf;
	apdu.lc = p - sbuf;
	apdu.datalen = p - sbuf;

	r = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, r, "APDU transmit failed");


	if (apdu.resplen != datalen || memcmp(rbuf, data, datalen) != 0) {
		sc_log(card->ctx, "The initial APDU did not return the same data");
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INTERNAL);
	}


	sc_format_apdu(card, &apdu, SC_APDU_CASE_2, 0x2A, 0x9E, 0x9A);
	apdu.resp = out;
	apdu.resplen = outlen;
	apdu.le = outlen;
	if (apdu.le > sc_get_max_recv_size(card)) {


		apdu.le = sc_get_max_recv_size(card);
	}

	apdu.data = NULL;
	apdu.datalen = 0;
	apdu.lc = 0;
	r = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, r, "APDU transmit failed");

	if (apdu.sw1 == 0x90 && apdu.sw2 == 0x00)
		LOG_FUNC_RETURN(card->ctx, apdu.resplen);

	r = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(card->ctx, r, "Card returned error");

	LOG_FUNC_RETURN(card->ctx, r);
}
