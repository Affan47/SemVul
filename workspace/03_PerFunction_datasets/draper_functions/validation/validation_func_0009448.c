parse_speeds(struct options *op, char *arg)
{
	char *cp;


	debug("entered parse_speeds\n");
	while ((cp = strsep(&arg, ",")) != NULL) {
		op->speeds[op->numspeed] = bcode(cp);
		if (op->speeds[op->numspeed] < 0)
			bb_error_msg_and_die("bad speed: %s", cp);

		op->numspeed++;
		if (op->numspeed > MAX_SPEED)
			bb_error_msg_and_die("too many alternate speeds");
	}
	debug("exiting parse_speeds\n");
}
