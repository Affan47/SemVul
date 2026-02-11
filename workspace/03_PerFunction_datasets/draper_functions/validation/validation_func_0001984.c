join_cont_lines(char *buffer)
{
    while ((buffer = strchr(buffer, '\n')))
	if (IS_SPACE(buffer[1])) {
	    if (buffer[-1] == '\r')
		buffer[-1] = ' ';
	    *buffer++ = ' ';
	} else {
	    if (buffer[-1] == '\r')
		buffer[-1] = '\0';
	    *buffer++ = '\0';
	    if (*buffer == '\0')
		return NULL;
	    else
		return buffer;
	    break;
	}

    return NULL;
}
