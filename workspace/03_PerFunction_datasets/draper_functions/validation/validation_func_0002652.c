sge_propagate_queue_suspension(const char *qnm, int how)
{
   lListElem *jep, *jatep;

   DENTER(TOP_LAYER, "sge_propagate_queue_suspension");

   DPRINTF(("searching for all jobs in queue %s due to %s\n", qnm, sge_sig2str(how)));
   for_each (jep, *object_type_get_master_list(SGE_TYPE_JOB)) {
      for_each (jatep, lGetList(jep, JB_ja_tasks)) {
         if (lGetElemStr(lGetList(jatep, JAT_granted_destin_identifier_list), JG_qname, qnm)) {
            u_long32 jstate;
            DPRINTF(("found "sge_u32"."sge_u32"\n", lGetUlong(jep, JB_job_number), lGetUlong(jatep, JAT_task_number)));
            jstate = lGetUlong(jatep, JAT_state);
            if (how == SGE_SIGSTOP)
               jstate |= JSUSPENDED_ON_SUBORDINATE;
            else
               jstate &= ~JSUSPENDED_ON_SUBORDINATE;
            lSetUlong(jatep, JAT_state, jstate);
         }
      }
   }

   DRETURN_VOID;
}
