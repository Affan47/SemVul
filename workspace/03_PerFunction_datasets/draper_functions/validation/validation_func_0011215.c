rcpt(int smtp, const char *recipients)
{
	List *list = split(recipients, ", ");

	if (!list || list_length(list) <= 0)
		return -1;

	while (list_has_next(list) == 1)
	{
		char *recipient = cstr((String *)list_next(list));
		int rc, code;

		if (net_send(smtp, 10, "RCPT TO: <%s>\r\n", recipient) == -1 ||
			(rc = net_expect(smtp, 10, "%d", &code)) == -1)
		{
			list_release(list);
			return -1;
		}

		if (rc != 1 || code != 250)
		{
			list_release(list);
			return set_errno(EPROTO);
		}
	}

	list_release(list);
	return 0;
}
