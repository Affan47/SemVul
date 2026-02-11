Bgetdf(void *vp)
{
	int c;
	struct bgetd *bg = vp;

	c = Bgetc(bg->b);
	if(c == Beof)
		bg->eof = 1;
	return c;
}
