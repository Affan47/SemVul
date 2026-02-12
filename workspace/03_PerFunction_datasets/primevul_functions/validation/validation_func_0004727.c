iasecc_pin_get_info(struct sc_card *card, struct sc_pin_cmd_data *data, int *tries_left)
{
	struct sc_context *ctx = card->ctx;
	struct iasecc_pin_policy policy;
	int rv;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "iasecc_pin_get_info(card:%p)", card);


	rv = iasecc_pin_get_status(card, data, tries_left);
	LOG_TEST_RET(ctx, rv, "Failed to get PIN status");

	rv = iasecc_pin_get_policy(card, data, &policy);
	LOG_TEST_RET(ctx, rv, "Failed to get PIN policy");


	data->pin1.max_tries = policy.tries_maximum;
	if (policy.tries_remaining >= 0)
		data->pin1.tries_left = policy.tries_remaining;

	if (tries_left)
		*tries_left = data->pin1.tries_left;

	LOG_FUNC_RETURN(ctx, rv);
}
