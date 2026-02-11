fr_set_dumpable(void)
{


	if (!allow_core_dumps) {
#ifdef HAVE_SYS_RESOURCE_H
		struct rlimit no_core;


		no_core.rlim_cur = 0;
		no_core.rlim_max = 0;

		if (setrlimit(RLIMIT_CORE, &no_core) < 0) {
			radlog(L_ERR, "Failed disabling core dumps: %s",
			       strerror(errno));
		}
#endif
		return;
	}


#ifdef HAVE_SYS_PRCTL_H
#ifdef PR_SET_DUMPABLE
	if (prctl(PR_SET_DUMPABLE, 1) < 0) {
		radlog(L_ERR,"Cannot re-enable core dumps: prctl(PR_SET_DUMPABLE) failed: '%s'",
		       strerror(errno));
	}
#endif
#endif


#ifdef HAVE_SYS_RESOURCE_H
	if (setrlimit(RLIMIT_CORE, &core_limits) < 0) {
		radlog(L_ERR, "Cannot update core dump limit: %s",
		       strerror(errno));
	}
#endif
}
