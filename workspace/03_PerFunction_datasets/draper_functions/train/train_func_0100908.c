do_timeout(int x)
{
	(void)x;
	if (timeout_flag == 0) {
		timeout_flag = 1;
		alarm(2);
		signal(SIGALRM, do_timeout);
	} else {

		exit(1);
	}
}
