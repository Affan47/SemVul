db_list_job_records(JCR *jcr, B_DB *mdb, JOB_DBR *jr, DB_LIST_HANDLER *sendit,
                    void *ctx, e_list_type type)
{
   char ed1[50];
   char limit[100];
   char esc[MAX_ESCAPE_NAME_LENGTH];

   db_lock(mdb);
   if (jr->limit > 0) {
      snprintf(limit, sizeof(limit), " LIMIT %d", jr->limit);
   } else {
      limit[0] = 0;
   }
   if (type == VERT_LIST) {
      if (jr->JobId == 0 && jr->Job[0] == 0) {
         Mmsg(mdb->cmd,
            "SELECT JobId,Job,Job.Name,PurgedFiles,Type,Level,"
            "Job.ClientId,Client.Name as ClientName,JobStatus,SchedTime,"
            "StartTime,EndTime,RealEndTime,JobTDate,"
            "VolSessionId,VolSessionTime,JobFiles,JobErrors,"
            "JobMissingFiles,Job.PoolId,Pool.Name as PooLname,PriorJobId,"
            "Job.FileSetId,FileSet.FileSet "
            "FROM Job,Client,Pool,FileSet WHERE "
            "Client.ClientId=Job.ClientId AND Pool.PoolId=Job.PoolId "
            "AND FileSet.FileSetId=Job.FileSetId  ORDER BY StartTime%s", limit);
      } else {
         Mmsg(mdb->cmd,
            "SELECT JobId,Job,Job.Name,PurgedFiles,Type,Level,"
            "Job.ClientId,Client.Name,JobStatus,SchedTime,"
            "StartTime,EndTime,RealEndTime,JobTDate,"
            "VolSessionId,VolSessionTime,JobFiles,JobErrors,"
            "JobMissingFiles,Job.PoolId,Pool.Name as PooLname,PriorJobId,"
            "Job.FileSetId,FileSet.FileSet "
            "FROM Job,Client,Pool,FileSet WHERE Job.JobId=%s AND "
            "Client.ClientId=Job.ClientId AND Pool.PoolId=Job.PoolId "
            "AND FileSet.FileSetId=Job.FileSetId",
            edit_int64(jr->JobId, ed1));
      }
   } else {
      if (jr->Name[0] != 0) {
         mdb->db_escape_string(jcr, esc, jr->Name, strlen(jr->Name));
         Mmsg(mdb->cmd,
           "SELECT JobId,Name,StartTime,Type,Level,JobFiles,JobBytes,JobStatus "
             "FROM Job WHERE Name='%s' ORDER BY StartTime,JobId ASC", esc);
      } else if (jr->Job[0] != 0) {
         mdb->db_escape_string(jcr, esc, jr->Job, strlen(jr->Job));
         Mmsg(mdb->cmd,
            "SELECT JobId,Name,StartTime,Type,Level,JobFiles,JobBytes,JobStatus "
            "FROM Job WHERE Job='%s' ORDER BY StartTime,JobId ASC", esc);
      } else if (jr->JobId != 0) {
         Mmsg(mdb->cmd,
            "SELECT JobId,Name,StartTime,Type,Level,JobFiles,JobBytes,JobStatus "
            "FROM Job WHERE JobId=%s", edit_int64(jr->JobId, ed1));
      } else {
         Mmsg(mdb->cmd,
           "SELECT JobId,Name,StartTime,Type,Level,JobFiles,JobBytes,JobStatus "
           "FROM Job ORDER BY StartTime,JobId ASC%s", limit);
      }
   }
   if (!QUERY_DB(jcr, mdb, mdb->cmd)) {
      db_unlock(mdb);
      return;
   }
   list_result(jcr, mdb, sendit, ctx, type);

   sql_free_result(mdb);
   db_unlock(mdb);
}
