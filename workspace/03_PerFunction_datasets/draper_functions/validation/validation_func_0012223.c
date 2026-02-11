setNameValue(char *arg)
{
    char *p;
    char *rhs = "true";

    if ((p = strchr(arg, '='))) {
	*p++ = '\0';
	rhs = p;
    }
    if (G_cnt >= G_sz) {
	G_sz += G_CHUNK;
	G_args = RALLOC(G_sz, G_args, attr_t);
    }
    G_args[G_cnt].name = arg;
    G_args[G_cnt].value = rhs;
    G_cnt++;

    return 0;
}
