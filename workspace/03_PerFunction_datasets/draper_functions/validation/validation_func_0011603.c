cleanup()
{
    sys_cleanup();

    if (ttyfd >= 0)
	close_tty();

    if (pidfilename[0] != 0 && unlink(pidfilename) < 0 && errno != ENOENT)
	syslog(LOG_WARNING, "unable to delete pid file: %m");
    pidfilename[0] = 0;

    if (locked)
	unlock();
}
