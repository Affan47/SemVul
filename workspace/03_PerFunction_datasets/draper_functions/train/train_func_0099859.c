cursor_up(int n)
{
	ofs -= n;
	if (ofs < 0) ofs = 0;
	return n;
}
