do_system(const char *cmd)
{
    int ierr;


    if (!cmd)
	return;
    restrict_popen();
#if defined(_WIN32) && !defined(WGP_CONSOLE)

    WinOpenConsole();
#endif
#if defined(_WIN32) && !defined(HAVE_BROKEN_WSYSTEM)
    {
	LPWSTR wcmd = UnicodeText(cmd, encoding);
	ierr = _wsystem(wcmd);
	free(wcmd);
    }
#else
    ierr = system(cmd);
#endif
    report_error(ierr);
}
