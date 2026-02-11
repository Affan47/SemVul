pthread_atfork_child()
{
  if (!pthread_atfork_enabled) {
    return;
  }
  pthread_atfork_enabled = false;
  long host = dmtcp::UniquePid::ThisProcess().hostid();
  dmtcp::UniquePid parent = dmtcp::UniquePid::ThisProcess();
  dmtcp::UniquePid child = dmtcp::UniquePid(host, -1, child_time);
  dmtcp::string child_name = jalib::Filesystem::GetProgramName() + "_(forked)";


  dmtcp_reset_gettid();
  JALIB_RESET_ON_FORK();
  _dmtcp_remutex_on_fork();
  dmtcp::SyslogCheckpointer::resetOnFork();
  dmtcp::ThreadSync::resetLocks();

  child = dmtcp::UniquePid(host, _real_getpid(), child_time);
  dmtcp::UniquePid::resetOnFork(child);
  dmtcp::Util::initializeLogFile(child_name);

#ifdef PID_VIRTUALIZATION
  if (dmtcp::VirtualPidTable::isConflictingPid(_real_getpid())) {
    _exit(DMTCP_FAIL_RC);
  }
  dmtcp::VirtualPidTable::instance().resetOnFork();
#endif

  JTRACE("fork()ed [CHILD]") (child) (parent);
  dmtcp::DmtcpWorker::resetOnFork(coordinatorAPI.coordinatorSocket());

}
