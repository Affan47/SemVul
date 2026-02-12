static int coolkey_match_card(sc_card_t *card)
{
	int r;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);


	card->ops->logout = NULL;

	r = coolkey_select_applet(card);
	if (r == SC_SUCCESS) {
		sc_apdu_t apdu;


		sc_format_apdu(card, &apdu, SC_APDU_CASE_1, COOLKEY_INS_GET_STATUS, 0x01, 0x00);
		apdu.cla = COOLKEY_CLASS;
		apdu.le = 0x00;
		apdu.resplen = 0;
		apdu.resp = NULL;
		r = sc_transmit_apdu(card, &apdu);
		if (r == SC_SUCCESS && apdu.sw1 == 0x6d && apdu.sw2 == 0x00) {
			return 1;
		}
		return 0;
	}
	return 0;
}
