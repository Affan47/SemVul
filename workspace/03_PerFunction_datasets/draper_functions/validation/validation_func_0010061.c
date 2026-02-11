ptf_init(void)
{
   DENTER(TOP_LAYER, "ptf_init");
   lInit(nmv);

   ptf_jobs = lCreateList("ptf_job_list", JL_Type);
   if (ptf_jobs == NULL) {
      DEXIT;
      return -1;
   }

   sge_switch2start_user();
   if (psStartCollector()) {
      sge_switch2admin_user();
      DEXIT;
      return -1;
   }
#if defined(__sgi)
   schedctl(RENICE, 0, 0);
#elif defined(CRAY)

   if (getuid() == 0) {
      int nice;

      if ((nice = nicem(C_PGRP, 0, 0)) > 0) {
         if (nicem(C_PGRP, 0, 0 - nice) < 0) {
            ERROR((SGE_EVENT, MSG_PRIO_NICEMFAILED_S, strerror(errno)));
         }
      }
   }
#elif defined(NECSX5) || defined(NECSX6)

   if (getuid() == 0) {
      if (nicex(0, -10) == -1) {
	 ERROR((SGE_EVENT, MSG_PRIO_NICEMFAILED_S, strerror(errno)));
      }
   }

#elif defined(ALPHA) || defined(SOLARIS) || defined(LINUX) || defined(FREEBSD) || defined(DARWIN)
   if (getuid() == 0) {
      if (setpriority(PRIO_PROCESS, getpid(), PTF_MAX_PRIORITY) < 0) {
         ERROR((SGE_EVENT, MSG_PRIO_SETPRIOFAILED_S, strerror(errno)));
      }
   }
#endif
   sge_switch2admin_user();
   DEXIT;
   return 0;
}
