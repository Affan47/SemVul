setnetmask(argv)
    char **argv;
{
    u_int32_t mask;

    if ((mask = inet_addr(*argv)) == -1 || (netmask & ~mask) != 0) {
	fprintf(stderr, "Invalid netmask %s\n", *argv);
	return 0;
    }

    netmask = mask;
    return (1);
}
