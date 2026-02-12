fmtstr(char *value, int leftjust, int minlen, int maxwidth,
	   int pointflag, PrintfTarget *target)
{
	int			padlen,
				vallen;


	if (pointflag)
		vallen = pg_strnlen(value, maxwidth);
	else
		vallen = strlen(value);

	adjust_padlen(minlen, vallen, leftjust, &padlen);

	while (padlen > 0)
	{
		dopr_outch(' ', target);
		--padlen;
	}

	dostr(value, vallen, target);

	trailing_pad(&padlen, target);
}
