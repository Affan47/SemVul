skipOverCComment (void)
{
	int c = fileGetc ();

	while (c != EOF)
	{
		if (c != '*')
			c = fileGetc ();
		else
		{
			const int next = fileGetc ();

			if (next != '/')
				c = next;
			else
			{
				c = SPACE;
				break;
			}
		}
	}
	return c;
}
