next_hash_space()
{
	int i = -1;
	do
	{
		++i;
	} while (symbol_hash[i].name[0] != '\0' && i < HASH_SIZE);

	if(symbol_hash[i].name[0] == '\0')
	{
		return i;
	} else {
		return -1;
	}
}
