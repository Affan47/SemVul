fgetjis(jp, fp)
jisbuf *jp;
XFILE *fp;
{
	char buf[MAXKLEN * R_MAXKANA + 1];
	int n;

	for (n = 0; n < jp -> max; n++) {
		VOID_C jis2str(buf, jp -> buf[n]);
		kanjifputs(buf, fp);
	}
}
