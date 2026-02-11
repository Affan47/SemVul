NsInitConf(void)
{
    Ns_DString addr;
    static char cwd[PATH_MAX];
    extern char *nsBuildDate;

    Ns_ThreadSetName("-main-");


    nsconf.build	 = nsBuildDate;
    nsconf.name          = NSD_NAME;
    nsconf.version       = NSD_VERSION;
    nsconf.tcl.version	 = TCL_VERSION;
    nsconf.http.major    = HTTP_MAJOR;
    nsconf.http.minor    = HTTP_MINOR;
    time(&nsconf.boot_t);
    nsconf.pid = getpid();
    nsconf.home = getcwd(cwd, sizeof(cwd));
    if (gethostname(nsconf.hostname, sizeof(nsconf.hostname)) != 0) {
        strcpy(nsconf.hostname, "localhost");
    }
    Ns_DStringInit(&addr);
    if (Ns_GetAddrByHost(&addr, nsconf.hostname)) {
        strcpy(nsconf.address, addr.string);
    } else {
        strcpy(nsconf.address, "0.0.0.0");
    }
    Ns_DStringFree(&addr);


    nsconf.shutdowntimeout = SHUTDOWNTIMEOUT;
    nsconf.sched.maxelapsed = SCHED_MAXELAPSED;
    nsconf.backlog = LISTEN_BACKLOG;
    nsconf.http.major = HTTP_MAJOR;
    nsconf.http.minor = HTTP_MINOR;
    nsconf.tcl.lockoninit = TCL_INITLCK;


    Ns_MutexSetName(&nsconf.state.lock, "nsd:state");
    nsconf.state.started = 1;
}
