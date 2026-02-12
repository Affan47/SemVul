req_more_codes_from_term(void)
{
    char	buf[23];
    int		old_idx = xt_index_out;


    if (exiting)
	return;


    while (xt_index_out < xt_index_in + 10 && key_names[xt_index_out] != NULL)
    {
	char *key_name = key_names[xt_index_out];

	MAY_WANT_TO_LOG_THIS;
	LOG_TR(("Requesting XT %d: %s", xt_index_out, key_name));
	sprintf(buf, "\033P+q%02x%02x\033\\", key_name[0], key_name[1]);
	out_str_nf((char_u *)buf);
	++xt_index_out;
    }


    if (xt_index_out != old_idx)
	out_flush();
}
