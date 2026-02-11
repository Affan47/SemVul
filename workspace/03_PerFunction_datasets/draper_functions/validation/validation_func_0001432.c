readFromDevice()
{
	int c;
	int n;
	if ((n = readOne()) == -1) return -1;
	if (n >= '0' && n <= '9')
		c = n - '0';
	else if (n >= 'A' && n <= 'F')
		c = n - 'A' + 10;
	else if (n >= 'a' && n <= 'f')
		c = n - 'a' + 10;
	else throw DataFormatException();
	c <<= 4;
	if ((n = readOne()) == -1) throw DataFormatException();
	if (n >= '0' && n <= '9')
		c |= n - '0';
	else if (n >= 'A' && n <= 'F')
		c |= n - 'A' + 10;
	else if (n >= 'a' && n <= 'f')
		c |= n - 'a' + 10;
	else throw DataFormatException();
	return c;
}
