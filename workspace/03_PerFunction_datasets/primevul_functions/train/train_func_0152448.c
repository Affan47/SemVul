parse_omit_name(
    XOC		oc,
    FontData	font_data,
    char	*pattern)
{
    char*	last = (char *) NULL;
    char*	base_name;
    char	buf[XLFD_MAX_LEN + 1];
    int		length = 0;
    int		num_fields;


    if(is_match_charset(font_data, pattern) == True) {
	if ((font_data->xlfd_name = get_font_name(oc, pattern)) != NULL) {
	    return True;
	}
    }

    length = strlen (pattern);

    if (length > XLFD_MAX_LEN)
	return -1;

    strcpy(buf, pattern);
    last = buf + length - 1;


    for (num_fields = 0, base_name = buf; *base_name != '\0'; base_name++)
	if (*base_name == '-') num_fields++;

    switch (num_fields) {
    case 12:


	if (*(last) == '-')
	    *++last = '*';

	*++last = '-';
	break;
    case 13:


	last = strrchr (buf, '-');
	num_fields = 12;
	break;
    case 14:


	last = strrchr (buf, '-');
	*last = '\0';
	last = strrchr (buf, '-');
	num_fields = 12;
	break;
    default:
	if (*last != '-')
	    *++last = '-';
	break;
    }


    last++;

    if ((last - buf) + strlen(font_data->name) > XLFD_MAX_LEN)
	return -1;

    strcpy(last, font_data->name);
    if ((font_data->xlfd_name = get_font_name(oc, buf)) != NULL)
	return True;


    if (num_fields < 12) {
	if ((last - buf) > (XLFD_MAX_LEN - 2))
	    return -1;
	*last = '*';
	*(last + 1) = '-';
	strcpy(last + 2, font_data->name);
	num_fields++;
	last+=2;
	if ((font_data->xlfd_name = get_font_name(oc, buf)) != NULL)
	    return True;
    }


    return False;
}
