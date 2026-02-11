drv_EFN_clear(void)
{
    char *cmd;
    int max_char, max_cmd, k;

    max_char = DROWS * DCOLS;
    max_cmd = 3 * max_char;

    if ((cmd = malloc(max_cmd)) == NULL) {
	error("%s : Failed to allocate memory in drv_Sample_write\n", Name);

    } else {

	for (k = 0; k < max_char; k++) {
	    cmd[(3 * k) + 0] = 0xff;
	    cmd[(3 * k) + 1] = k + 1;
	    cmd[(3 * k) + 2] = ' ';
	}
	drv_EFN_send(cmd, max_cmd);
	drv_EFN_send(cmd, max_cmd);
	free(cmd);

    }
}
