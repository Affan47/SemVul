strcins(char *s, int p, char c)
{
	int n;
	for (n=strlen(s)-p; n>=0; n-- )
		*(s+p+n+1) = *(s+p+n);
	*(s+p) = c;
}
