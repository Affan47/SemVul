inc_dec_var(u_char value)
{
	struct st_var_header *p_header;
	struct var_t *var_data;
	char num_buf[32];
	char *cp = num_buf;
	char *pn;
	int var_id = (int)value - VAR_START;
	int how = (var_id & 1) ? E_INC : E_DEC;

	var_id = var_id / 2 + FIRST_SET_VAR;
	p_header = spk_get_var_header(var_id);
	if (p_header == NULL)
		return -1;
	if (p_header->var_type != VAR_NUM)
		return -1;
	var_data = p_header->data;
	if (spk_set_num_var(1, p_header, how) != 0)
		return -1;
	if (!spk_close_press) {
		for (pn = p_header->name; *pn; pn++) {
			if (*pn == '_')
				*cp = SPACE;
			else
				*cp++ = *pn;
		}
	}
	snprintf(cp, sizeof(num_buf) - (cp - num_buf), " %d ",
		 var_data->u.n.value);
	synth_printf("%s", num_buf);
	return 0;
}
