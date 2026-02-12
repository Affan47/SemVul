static void setup_private_pts(void)
{


	struct stat st;


	if (stat("/dev/pts/ptmx", &st) != 0) {
		die("cannot stat /dev/pts/ptmx");
	}

	if (stat("/dev/ptmx", &st) != 0) {
		die("cannot stat /dev/ptmx");
	}


	sc_do_mount("devpts", "/dev/pts", "devpts", MS_MGC_VAL,
		    "newinstance,ptmxmode=0666,mode=0620,gid=5");
	sc_do_mount("/dev/pts/ptmx", "/dev/ptmx", "none", MS_BIND, 0);
}
