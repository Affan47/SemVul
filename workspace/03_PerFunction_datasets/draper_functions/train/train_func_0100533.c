ParseNumber(TREE * tree)
{
	long	value;
	int	ch;

	value = 0;
	ch = *tree->cp++;

	if (!isDigit(ch))
	{
		tree->cp--;

		return BadToken(tree, "Number expected");
	}


	if (ch != '0')
	{
		while (isDigit(ch))
		{
			value = value * 10 + ch - '0';
			ch = *tree->cp++;
		}

		tree->cp--;

		if (isSymbol(ch))
			return BadToken(tree, "Bad decimal number");

		tree->tokenInt = value;

		return TOKEN_NUMBER;
	}


	ch = *tree->cp++;

	if ((ch != 'x') && (ch != 'X'))
	{
		while (isOctal(ch))
		{
			value = value * 8 + ch - '0';
			ch = *tree->cp++;
		}

		tree->cp--;

		if (isSymbol(ch))
			return BadToken(tree, "Bad octal number");

		tree->tokenInt = value;

		return TOKEN_NUMBER;
	}


	ch = *tree->cp++;

	while (isHex(ch))
	{
		value = value * 16;

		if (isDigit(ch))
			value += (ch - '0');
		else if (isLower(ch))
			value += (ch - 'a' + 10);
		else
			value += (ch - 'A' + 10);

		ch = *tree->cp++;
	}

	tree->cp--;

	if (isSymbol(ch))
		return BadToken(tree, "Bad hex number");

	tree->tokenInt = value;

	return TOKEN_NUMBER;
}
