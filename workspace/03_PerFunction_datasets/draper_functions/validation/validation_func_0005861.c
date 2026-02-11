UpMotion(destline)
register int	destline;
{
	register int	nchars = CapLine - destline;

	while (--nchars >= 0) {
		putpad(UP, 1);
		CapLine = destline;
	}
}
