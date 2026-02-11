reporting_create_acct_record(sge_gdi_ctx_class_t *ctx,
                       lList **answer_list,
                       lListElem *job_report,
                       lListElem *job, lListElem *ja_task, bool intermediate)
{
   bool ret = true;
   char category_buffer[MAX_STRING_SIZE];
   dstring category_dstring;
   dstring job_dstring = DSTRING_INIT;
   const char *category_string = NULL;
   const char *job_string = NULL;
   bool do_reporting  = mconf_get_do_reporting();
   bool do_accounting = mconf_get_do_accounting();
   const char *acct_file = ctx->get_acct_file(ctx);

   DENTER(TOP_LAYER, "reporting_create_acct_record");


   if (do_reporting || do_accounting) {

      sge_dstring_init(&category_dstring, category_buffer,
                       sizeof(category_buffer));

      sge_build_job_category_dstring(&category_dstring, job,
                                     *(userset_list_get_master_list()), *object_type_get_master_list(SGE_TYPE_PROJECT), NULL,
                                     *object_type_get_master_list(SGE_TYPE_RQS));
      category_string = sge_dstring_get_string(&category_dstring);


      if (do_accounting && !intermediate) {
         job_string = sge_write_rusage(&job_dstring, job_report, job, ja_task,
                                       category_string, REPORTING_DELIMITER,
                                       false);
         if (job_string == NULL) {
            ret = false;
         } else {

            rep_buf_t *buf = &reporting_buffer[ACCOUNTING_BUFFER];
            sge_mutex_lock(buf->mtx_name, SGE_FUNC, __LINE__, &(buf->mtx));
            sge_dstring_append(&(buf->buffer), job_string);
            sge_mutex_unlock(buf->mtx_name, SGE_FUNC, __LINE__, &(buf->mtx));
         }


         if (mconf_get_accounting_flush_time() == 0) {
            ret = (reporting_flush_accounting(acct_file, answer_list) != 0) ? true : false;
         }
      }


      if (ret && do_reporting) {


         bool intermediate_written = intermediate_usage_written(job_report, ja_task);
         bool do_intermediate = (intermediate_written || intermediate) ? true : false;

         if (job_string == NULL || do_intermediate) {
            sge_dstring_clear(&job_dstring);
            job_string = sge_write_rusage(&job_dstring, job_report, job, ja_task,
                                          category_string, REPORTING_DELIMITER,
                                          do_intermediate);
         }
         if (job_string == NULL) {
            ret = false;
         } else {
            ret = reporting_create_record(answer_list, "acct", job_string);
         }
      }
   }

   sge_dstring_free(&job_dstring);

   DRETURN(ret);
}
