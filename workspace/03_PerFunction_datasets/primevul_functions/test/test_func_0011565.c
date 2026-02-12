nv_K_getcmd(
	cmdarg_T	*cap,
	char_u		*kp,
	int		kp_help,
	int		kp_ex,
	char_u		**ptr_arg,
	int		n,
	char_u		*buf,
	unsigned	buflen)
{
    char_u	*ptr = *ptr_arg;
    int		isman;
    int		isman_s;

    if (kp_help)
    {

	STRCPY(buf, "he! ");
	return n;
    }

    if (kp_ex)
    {

	if (cap->count0 != 0)
	    vim_snprintf((char *)buf, buflen, "%s %ld", kp, cap->count0);
	else
	    STRCPY(buf, kp);
	STRCAT(buf, " ");
	return n;
    }


    while (*ptr == '-' && n > 0)
    {
	++ptr;
	--n;
    }
    if (n == 0)
    {

	emsg(_(e_no_identifier_under_cursor));
	vim_free(buf);
	*ptr_arg = ptr;
	return 0;
    }


    isman = (STRCMP(kp, "man") == 0);
    isman_s = (STRCMP(kp, "man -s") == 0);
    if (cap->count0 != 0 && !(isman || isman_s))
	sprintf((char *)buf, ".,.+%ld", cap->count0 - 1);

    STRCAT(buf, "! ");
    if (cap->count0 == 0 && isman_s)
	STRCAT(buf, "man");
    else
	STRCAT(buf, kp);
    STRCAT(buf, " ");
    if (cap->count0 != 0 && (isman || isman_s))
    {
	sprintf((char *)buf + STRLEN(buf), "%ld", cap->count0);
	STRCAT(buf, " ");
    }

    *ptr_arg = ptr;
    return n;
}
