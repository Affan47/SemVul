ExitPostmaster(int status)
{
#ifdef HAVE_PTHREAD_IS_THREADED_NP


	if (pthread_is_threaded_np() != 0)
		ereport(LOG,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg_internal("postmaster became multithreaded"),
				 errdetail("Please report this to <%s>.", PACKAGE_BUGREPORT)));
#endif


	proc_exit(status);
}
