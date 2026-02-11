scanint(pi, str)
int	*pi;
char	*str;
{

	while (*str) {
		if  ((sscanf(str, "%d,", pi++)) < 1)
			bug(41);
		while (*str++ != ',')
			;
	}
	return;
}
