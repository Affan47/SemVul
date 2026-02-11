get_all_bodies(struct sip_msg * msg)
{
	char * start = 0, * end;
	int type = 0;
	struct part ** cur, * temp;
	str delimiter;


	if (msg->multi)
		return msg->multi;

	start = get_body(msg);

	if (start == NULL || msg->content_length == NULL )
		return 0;

	if (msg->buf + msg->len - start < get_content_length(msg))
	{
		LM_ERR("Message is shorter than indicated by content length:"
			" got %d expected %ld\n", (int)(msg->buf + msg->len - start),
			get_content_length(msg));
		return NULL;
	}

	type = parse_content_type_hdr(msg);


	if (type <= 0)
		return 0;


	msg->multi = pkg_malloc(sizeof (struct multi_body));

	if (msg->multi == 0)
	{
		LM_ERR("Unable to allocate memory\n");
		return 0;
	}
	memset(msg->multi, 0, sizeof (struct multi_body));

	msg->multi->boundary = ((content_t *) msg->content_type->parsed)->boundary;
	cur = &msg->multi->first;

	if ((type >> 16) == TYPE_MULTIPART)
	{
		msg->multi->from_multi_part = 1;

		delimiter = ((content_t*) msg->content_type->parsed)->boundary;

		LM_DBG("Starting parsing with boundary = [%.*s]\n", delimiter.len, delimiter.s);

		start = find_sdp_line_delimiter(start, msg->buf + msg->len, delimiter);
		while (1)
		{
			end = find_sdp_line_delimiter(start + 1, msg->buf + msg->len, delimiter);
			if (end == NULL)
				break;


			temp = parse_single_part(start + delimiter.len + 4, end-2);
			if (temp == NULL)
			{
				LM_ERR("Unable to parse part:[%.*s]\n",(int)(end-start),start);
				return 0;
			}


			*cur = temp;
			cur = &temp->next;
			start = end;
		}

	} else
	{
		msg->multi->from_multi_part = 0;


		if ((temp = new_part()) == 0)
			return 0;

		temp->content_type = type;

		temp->body.s = start;
		temp->body.len = get_content_length(msg);

		temp->all_data.s = start;
		temp->all_data.len = get_content_length(msg);

		*cur = temp;
		msg->multi->part_count++;


	}

	return msg->multi;

}
