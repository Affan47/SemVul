rosh_run(int argc, char *argv[])
{
    char cmdstr[ROSH_CMD_SZ];
    int len;

    len = rosh_argcat(cmdstr, ROSH_CMD_SZ, argc, argv, 0);
    if (len) {
	printf("--run: '%s'\n", cmdstr);
	syslinux_run_command(cmdstr);
    } else {
	printf(APP_NAME ":run: No arguments\n");
    }
}
