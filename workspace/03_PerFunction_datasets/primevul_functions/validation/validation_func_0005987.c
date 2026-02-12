static int cardos_finish(sc_card_t *card)
{
	int r = 0;

	if (card == NULL )
		return 0;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);


	if (card->drv_data) {
		free(card->drv_data);
		card->drv_data = NULL;
	}

	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, r);
}
