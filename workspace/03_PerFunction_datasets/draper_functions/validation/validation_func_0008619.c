release_successor_jobs_ad(lListElem *jep)
{
   lListElem *jid, *suc_jep;
   u_long32 job_ident;

   DENTER(TOP_LAYER, "release_successor_jobs_ad");

   for_each(jid, lGetList(jep, JB_ja_ad_successor_list)) {
      suc_jep = job_list_locate(*(object_type_get_master_list(SGE_TYPE_JOB)), lGetUlong(jid, JRE_job_number));
      if (suc_jep) {
         int Modified = 0;

         job_ident = lGetUlong(jep, JB_job_number);
         if (!lDelSubUlong(suc_jep, JRE_job_number, job_ident, JB_ja_ad_predecessor_list)) {
             DPRINTF(("no reference "sge_u32" and %s to job "sge_u32" in array predecessor list of job "sge_u32"\n",
               job_ident, lGetString(jep, JB_job_name),
               lGetUlong(suc_jep, JB_job_number), lGetUlong(jep, JB_job_number)));
         } else {
            if (lGetList(suc_jep, JB_ja_ad_predecessor_list)) {
               DPRINTF(("removed job "sge_u32"'s array dependance from exiting job "sge_u32"\n",
                  lGetUlong(suc_jep, JB_job_number), lGetUlong(jep, JB_job_number)));
            } else {
               DPRINTF(("job "sge_u32"'s job exit triggers release of array tasks in job "sge_u32"\n",
                  lGetUlong(jep, JB_job_number), lGetUlong(suc_jep, JB_job_number)));
            }
            Modified = 1;
         }

         if (Modified) {

            sge_task_depend_flush(suc_jep, NULL);
            sge_add_job_event(sgeE_JOB_MOD, suc_jep, NULL);
         }
      }
   }

   DEXIT;
   return;
}
