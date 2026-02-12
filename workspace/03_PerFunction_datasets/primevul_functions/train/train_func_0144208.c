static void sc_make_slave_mount_ns(void)
{
	if (unshare(CLONE_NEWNS) < 0) {
		die("can not unshare mount namespace");
	}


	sc_do_mount("none", "/", NULL, MS_REC | MS_SLAVE, NULL);
}
