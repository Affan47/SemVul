horizontalLine(int x, int y, int n, char_type c)
{
	for (int i = 0; i < n && i + x < xmax_; ++i)
		at(x + i, y) = c;
}
