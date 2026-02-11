opt2char(int option)
{
	const char *ptr;
	for (ptr = optflags; option > 1; option >>= 1, ptr++);

	return *ptr;
}
