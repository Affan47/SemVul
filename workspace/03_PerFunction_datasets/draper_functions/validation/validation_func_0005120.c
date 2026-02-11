japi_job_ps(const char *job_id_str, int *remote_ps, dstring *diag)
{
   u_long32 jobid, taskid;
   lList *retrieved_job_list = NULL;
   lList *retrieved_cqueue_list = NULL;
   int drmaa_errno;
   bool is_array_task;

   DENTER(TOP_LAYER, "japi_job_ps");


   if (!job_id_str || !remote_ps) {
      japi_standard_error(DRMAA_ERRNO_INVALID_ARGUMENT, diag);
      DRETURN(DRMAA_ERRNO_INVALID_ARGUMENT);
   }


   JAPI_LOCK_SESSION();
   if (japi_session != JAPI_SESSION_ACTIVE) {
      JAPI_UNLOCK_SESSION();
      japi_standard_error(DRMAA_ERRNO_NO_ACTIVE_SESSION, diag);
      DRETURN(DRMAA_ERRNO_NO_ACTIVE_SESSION);
   }


   japi_inc_threads(SGE_FUNC);

   JAPI_UNLOCK_SESSION();


   if (japi_init_mt(diag)!=DRMAA_ERRNO_SUCCESS) {
      japi_dec_threads(SGE_FUNC);

      DRETURN(DRMAA_ERRNO_INTERNAL_ERROR);
   }

   DPRINTF(("japi_job_ps1("SFQ")\n", job_id_str));
   if ((drmaa_errno=japi_parse_jobid(job_id_str, &jobid, &taskid,
         &is_array_task, diag)) !=DRMAA_ERRNO_SUCCESS) {
      japi_dec_threads(SGE_FUNC);

      DRETURN(drmaa_errno);
   }

   DPRINTF(("japi_job_ps2("SFQ")\n", job_id_str));

   drmaa_errno = japi_get_job(jobid, &retrieved_job_list, diag);
   if (drmaa_errno != DRMAA_ERRNO_SUCCESS) {
      japi_dec_threads(SGE_FUNC);

      DRETURN(drmaa_errno);
   }

   DPRINTF(("japi_job_ps3("SFQ")\n", job_id_str));

   drmaa_errno = japi_sge_state_to_drmaa_state(lFirst(retrieved_job_list),
                                               is_array_task, jobid, taskid,
                                               remote_ps, diag);


#if 0
   if (node) {
      const lListElem *ja_task, *master_node;
      switch (*remote_ps) {
      case DRMAA_PS_RUNNING:
      case DRMAA_PS_SYSTEM_SUSPENDED:
      case DRMAA_PS_USER_SUSPENDED:
      case DRMAA_PS_USER_SYSTEM_SUSPENDED:
         if ((ja_task = job_search_task(lFirst(retrieved_job_list), NULL, taskid)) &&
            (master_node = lFirst(lGetList(ja_task, JAT_granted_destin_identifier_list))))
            sge_dstring_copy_string(node, lGetHost(master_node, JG_qhostname));
         else
            sge_dstring_copy_string(node, "<unknown>");
         break;
      default:
         break;
      }
   }
#endif

   japi_dec_threads(SGE_FUNC);

   lFreeList(&retrieved_job_list);
   lFreeList(&retrieved_cqueue_list);

   DRETURN(drmaa_errno);
}
