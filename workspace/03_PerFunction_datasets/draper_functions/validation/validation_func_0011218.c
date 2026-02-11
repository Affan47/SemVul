get_option(void)
{
	int in = 0;
	do {
		printf("Option? [1..9] ");
		scanf("%d", &in);

		while(getchar() != '\n');
	} while (in < 1 || in > 9);
	return in;
}
