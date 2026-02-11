handle_disassoc(const u_char *p)
{
	struct mgmt_body_t  pbody;

	memset(&pbody, 0, sizeof(pbody));

	if (!TTEST2(*p, IEEE802_11_REASON_LEN))
		return 0;
	pbody.reason_code = EXTRACT_LE_16BITS(p);

	printf(": %s",
	    (pbody.reason_code < NUM_REASONS)
		? reason_text[pbody.reason_code]
		: "Reserved" );

	return 1;
}
