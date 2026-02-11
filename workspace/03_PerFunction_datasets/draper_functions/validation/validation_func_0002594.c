condattr_init(void)
{
        const char        *myname = "condattr_init";

	time_mono_init();

        if ( ( errno = pthread_condattr_init( &common_cond_attr ) ) )
                msglog(MSG_FATAL|LOG_ERRNO, "%s: pthread_condattr_init",
                        myname);

        if ( ( errno = pthread_condattr_setpshared( &common_cond_attr,
                                                PTHREAD_PROCESS_PRIVATE ) ) )
                msglog( MSG_FATAL|LOG_ERRNO, "%s: pthread_condattr_setpshared: " \
                        "PTHREAD_PROCESS_PRIVATE", myname);

#if defined _POSIX_CLOCK_SELECTION && _POSIX_CLOCK_SELECTION >= 0 \
			&& defined(_POSIX_TIMERS) && (_POSIX_TIMERS > 0)
        if ( ( errno = pthread_condattr_setclock(&common_cond_attr, clockid ) ) )
                msglog( MSG_FATAL|LOG_ERRNO, "%s: pthread_condattr_setclock",
                                                myname );
#endif
}
