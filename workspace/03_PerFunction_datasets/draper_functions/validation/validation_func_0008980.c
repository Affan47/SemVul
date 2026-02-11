str_cat(char *p, const char **q)
{
int	l=(int)(unsigned char)*(*q)++;

	while (*p)	p++;
	memcpy(p, *q, l);
	p[l]=0;
	*q += l;
}
