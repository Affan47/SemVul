diversion_param(struct sip_msg *msg, str name)
{
	struct to_param *params;

	if (parse_diversion_header(msg) == -1) {
		LM_ERR("could not get diversion parameter\n");
		return 0;
	}

	params =  ((struct to_body*)(msg->diversion->parsed))->param_lst;

	while (params) {
		if ((params->name.len == name.len) &&
		(strncmp(params->name.s, name.s, name.len) == 0)) {
			return &(params->value);
		}
		params = params->next;
	}

	return 0;
}
