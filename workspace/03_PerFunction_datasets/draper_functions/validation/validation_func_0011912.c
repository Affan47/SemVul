strins(char *str, const char *ins, int pos)
{
	char *cpy = strdup(str+pos);
	if(!cpy)
		return strlen(str);

	snprintf(str+pos, FM_BUFFER_SIZE-pos-1, "%s%s", ins, cpy);
	str[FM_BUFFER_SIZE - 1] = 0;
	free(cpy);
	return strlen(str);
}
