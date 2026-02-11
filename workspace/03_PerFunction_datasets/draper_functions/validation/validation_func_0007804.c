of10_desc_stats_reply_print(const u_char *cp, const u_char *ep, const u_int len) {
	if (len != OF_DESC_STATS_LEN)
		goto corrupt;

	TCHECK2(*cp, DESC_STR_LEN);
	printf("\n\t  mfr_desc '");
	fn_print(cp, cp + DESC_STR_LEN);
	printf("'");
	cp += DESC_STR_LEN;

	TCHECK2(*cp, DESC_STR_LEN);
	printf("\n\t  hw_desc '");
	fn_print(cp, cp + DESC_STR_LEN);
	printf("'");
	cp += DESC_STR_LEN;

	TCHECK2(*cp, DESC_STR_LEN);
	printf("\n\t  sw_desc '");
	fn_print(cp, cp + DESC_STR_LEN);
	printf("'");
	cp += DESC_STR_LEN;

	TCHECK2(*cp, SERIAL_NUM_LEN);
	printf("\n\t  serial_num '");
	fn_print(cp, cp + SERIAL_NUM_LEN);
	printf("'");
	cp += SERIAL_NUM_LEN;

	TCHECK2(*cp, DESC_STR_LEN);
	printf("\n\t  dp_desc '");
	fn_print(cp, cp + DESC_STR_LEN);
	printf("'");
	return cp + DESC_STR_LEN;

corrupt:
	printf(" (corrupt)");
	TCHECK2(*cp, len);
	return cp + len;
trunc:
	printf(" [|openflow]");
	return ep;
}
