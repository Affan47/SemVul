header_append_domain_buffer(char *buffer, char *domain, size_t len)
{
	size_t	i;
	int	escape, quote, comment, bracket;
	int	has_domain, has_bracket, has_group;
	int	pos_bracket, pos_component, pos_insert;
	char	copy[APPEND_DOMAIN_BUFFER_SIZE];

	escape = quote = comment = bracket = 0;
	has_domain = has_bracket = has_group = 0;
	pos_bracket = pos_insert = pos_component = 0;
	for (i = 0; buffer[i]; ++i) {
		if (buffer[i] == '(' && !escape && !quote)
			comment++;
		if (buffer[i] == '"' && !escape && !comment)
			quote = !quote;
		if (buffer[i] == ')' && !escape && !quote && comment)
			comment--;
		if (buffer[i] == '\\' && !escape && !comment && !quote)
			escape = 1;
		else
			escape = 0;
		if (buffer[i] == '<' && !escape && !comment && !quote && !bracket) {
			bracket++;
			has_bracket = 1;
		}
		if (buffer[i] == '>' && !escape && !comment && !quote && bracket) {
			bracket--;
			pos_bracket = i;
		}
		if (buffer[i] == '@' && !escape && !comment && !quote)
			has_domain = 1;
		if (buffer[i] == ':' && !escape && !comment && !quote)
			has_group = 1;


		if (!comment && buffer[i] != ')' && !isspace((unsigned char)buffer[i]))
			pos_component = i;
	}


	if (escape || quote || comment || bracket)
		return;


	if (has_domain)
		return;


	if (has_group)
		return;


	if (has_bracket) {
		pos_bracket--;
		while (isspace((unsigned char)buffer[pos_bracket]))
			pos_bracket--;
		if (buffer[pos_bracket] == '<')
			return;
		pos_insert = pos_bracket + 1;
	}
	else {

		pos_insert = pos_component + 1;


                if (buffer[pos_component] == '\0' ||
		    isspace((unsigned char)buffer[pos_component]))
                        return;
	}

	if (snprintf(copy, sizeof copy, "%.*s@%s%s",
		(int)pos_insert, buffer,
		domain,
		buffer+pos_insert) >= (int)sizeof copy)
		return;

	memcpy(buffer, copy, len);
}
