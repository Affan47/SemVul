list_scheduled_jobs(UAContext *ua)
{
   utime_t runtime;
   RUN *run;
   JOB *job;
   int level, num_jobs = 0;
   int priority;
   bool hdr_printed = false;
   dlist sched;
   sched_pkt *sp;
   int days, i;

   Dmsg0(200, "enter list_sched_jobs()\n");

   days = 1;
   i = find_arg_with_value(ua, NT_("days"));
   if (i >= 0) {
     days = atoi(ua->argv[i]);
     if (((days < 0) || (days > 500)) && !ua->api) {
       ua->send_msg(_("Ignoring invalid value for days. Max is 500.\n"));
       days = 1;
     }
   }


   LockRes();
   foreach_res(job, R_JOB) {
      if (!acl_access_ok(ua, Job_ACL, job->name()) || !job->enabled) {
         continue;
      }
      for (run=NULL; (run = find_next_run(run, job, runtime, days)); ) {
         USTORE store;
         level = job->JobLevel;
         if (run->level) {
            level = run->level;
         }
         priority = job->Priority;
         if (run->Priority) {
            priority = run->Priority;
         }
         if (!hdr_printed) {
            prt_runhdr(ua);
            hdr_printed = true;
         }
         sp = (sched_pkt *)malloc(sizeof(sched_pkt));
         sp->job = job;
         sp->level = level;
         sp->priority = priority;
         sp->runtime = runtime;
         sp->pool = run->pool;
         get_job_storage(&store, job, run);
         sp->store = store.store;
         Dmsg3(250, "job=%s store=%s MediaType=%s\n", job->name(), sp->store->name(), sp->store->media_type);
         sched.binary_insert_multiple(sp, my_compare);
         num_jobs++;
      }
   }
   UnlockRes();
   foreach_dlist(sp, &sched) {
      prt_runtime(ua, sp);
   }
   if (num_jobs == 0 && !ua->api) {
      ua->send_msg(_("No Scheduled Jobs.\n"));
   }
   if (!ua->api) ua->send_msg("====\n");
   Dmsg0(200, "Leave list_sched_jobs_runs()\n");
}
