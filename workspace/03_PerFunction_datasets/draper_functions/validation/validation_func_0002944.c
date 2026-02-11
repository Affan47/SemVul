unhex(unsigned char c)
{
    if (c < '@')
	return c - '0';
    return (c & 0x0f) + 9;
}
