readdec (char v, char **c)
{
    char nc;
    uae_u32 val;
    if (isdigit(v)) val = v - '0'; else return 0;

    while (isdigit(nc = **c)) {
	(*c)++;
	val *= 10;
	val += nc - '0';
    }
    return val;
}
