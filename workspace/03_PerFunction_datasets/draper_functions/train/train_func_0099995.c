spool_berkeleydb_default_delete_func(lList **answer_list,
                                   const lListElem *type,
                                   const lListElem *rule,
                                   const char *key,
                                   const sge_object_type object_type)
{
   bool ret = true;
   bool local_transaction = false;
   const char *table_name;
   bdb_info info;

   dstring dbkey_dstring;
   char dbkey_buffer[MAX_STRING_SIZE];
   const char *dbkey;

   DENTER(BDB_LAYER, "spool_berkeleydb_default_delete_func");

   sge_dstring_init(&dbkey_dstring, dbkey_buffer, sizeof(dbkey_buffer));
   info = (bdb_info)lGetRef(rule, SPR_clientdata);
   if (info == NULL) {
      answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                              ANSWER_QUALITY_WARNING,
                              MSG_BERKELEY_NOCONNECTIONOPEN_S,
                              lGetString(rule, SPR_url));
      ret = false;
   }

   if (ret) {
      ret = spool_berkeleydb_check_reopen_database(answer_list, info);
   }

   if (ret) {
      DB_TXN *txn = bdb_get_txn(info);

      if (txn == NULL) {
         ret = spool_berkeleydb_start_transaction(answer_list, info);
         if (ret) {
            local_transaction = true;
         }
      }

      if (ret) {
         switch (object_type) {
            case SGE_TYPE_CQUEUE:
               ret = spool_berkeleydb_delete_cqueue(answer_list, info, key);
               break;
            case SGE_TYPE_JOB:
            case SGE_TYPE_JATASK:
            case SGE_TYPE_PETASK:
               {
                  u_long32 job_id, ja_task_id;
                  char *pe_task_id;
                  char *dup = strdup(key);
                  bool only_job;

                  job_parse_key(dup, &job_id, &ja_task_id, &pe_task_id, &only_job);

                  if (pe_task_id != NULL) {
                     dbkey = sge_dstring_sprintf(&dbkey_dstring, "%8d.%8d %s",
                                                 job_id, ja_task_id, pe_task_id);
                     ret = spool_berkeleydb_delete_pe_task(answer_list, info,
                                                           dbkey, false);
                  } else if (ja_task_id != 0) {
                     dbkey = sge_dstring_sprintf(&dbkey_dstring, "%8d.%8d",
                                                 job_id, ja_task_id);
                     ret = spool_berkeleydb_delete_ja_task(answer_list, info,
                                                           dbkey, false);
                  } else {
                     dbkey = sge_dstring_sprintf(&dbkey_dstring, "%8d",
                                                 job_id);
                     ret = spool_berkeleydb_delete_job(answer_list, info,
                                                       dbkey, false);
                  }
                  FREE(dup);
               }
               break;
            case SGE_TYPE_JOBSCRIPT:
               {
                  const char *exec_file;
                  char *dup = strdup(key);
                  const char *db_key = jobscript_parse_key(dup, &exec_file);
                  ret = spool_berkeleydb_delete_object(answer_list, info,
                                                    BDB_JOB_DB,
                                                    db_key,
                                                    false);
                  FREE(dup);
               }
               break;
            default:
               table_name = object_type_get_name(object_type);
               dbkey = sge_dstring_sprintf(&dbkey_dstring, "%s:%s",
                                           table_name,
                                           key);

               ret = spool_berkeleydb_delete_object(answer_list, info,
                                                    BDB_CONFIG_DB,
                                                    dbkey, false);
               break;
         }


         if (local_transaction) {
            ret = spool_berkeleydb_end_transaction(answer_list, info, ret);
         }
      }
   }

   DEXIT;
   return ret;
}
