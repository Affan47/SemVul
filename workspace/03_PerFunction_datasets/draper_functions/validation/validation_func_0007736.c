Java_com_sleepycat_db_internal_db_1javaJNI_DbEnv_1memp_1sync(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jobject jarg2) {
  struct DbEnv *arg1 = (struct DbEnv *) 0 ;
  DB_LSN *arg2 = (DB_LSN *) 0 ;
  DB_LSN lsn2 ;
  db_ret_t result;

  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(struct DbEnv **)&jarg1;

  if (jarg2 == NULL) {
    arg2 = NULL;
  } else {
    arg2 = &lsn2;
    arg2->file = (*jenv)->GetIntField(jenv, jarg2, dblsn_file_fid);
    arg2->offset = (*jenv)->GetIntField(jenv, jarg2,
      dblsn_offset_fid);
  }


  if (jarg1 == 0) {
    __dbj_throw(jenv, EINVAL, "call on closed handle", NULL, NULL);
    return ;
  }


  errno = 0;
  result = (db_ret_t)DbEnv_memp_sync(arg1,arg2);
  if (!DB_RETOK_STD(errno)) {
    __dbj_throw(jenv, errno, NULL, NULL, JDBENV);
  }


  if (jarg2 != NULL) {
    (*jenv)->SetIntField(jenv, jarg2, dblsn_file_fid, arg2->file);
    (*jenv)->SetIntField(jenv, jarg2,
      dblsn_offset_fid, arg2->offset);
  }

}
