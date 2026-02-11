drawVerticalGrill (Window win, int x, int height)
{
	int y = 0;
	while (y < height - 5)
	{
		y += 3;
		draw_dot (win, x + 3, y);
		draw_dot (win, x + 6, y);
	}
}
