Xfputc(c, fp)
int c;
XFILE *fp;
{
	u_char uc;

	uc = (u_char)c;
	if (Xfwrite((char *)&uc, sizeof(uc), fp) < (int)sizeof(uc))
		return(EOF);

	return(c);
}
