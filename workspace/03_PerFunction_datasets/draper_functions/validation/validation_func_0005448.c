copy(void)
{
	long n;
	char buf[Bsize];
	while((n=tread(buf, Bsize)) > 0) {
		twrite(buf, n);
		Bflush(&bout);
	}
}
