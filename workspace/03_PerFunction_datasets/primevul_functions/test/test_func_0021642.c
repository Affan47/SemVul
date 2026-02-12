getNumber(widechar *string, widechar *number) {

	int k = 0;
	*number = 0;
	while (string[k] >= '0' && string[k] <= '9')
		*number = 10 * *number + (string[k++] - '0');
	return k;
}
