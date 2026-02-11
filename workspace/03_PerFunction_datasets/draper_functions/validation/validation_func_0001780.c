check_credentials(pid_t pid, pid_t ppid, pid_t pgrp, pid_t sid)
{
	int ret = 0;
	if( pid != getpid() )
		ret |= PID_MISM;
	if( ppid != getppid() )
		ret |= PPID_MISM;
	if( pgrp != getpgrp() )
		ret |= PGRP_MISM;
	if( sid != getsid(0) )
		ret |= SID_MISM;
	return ret;
}
