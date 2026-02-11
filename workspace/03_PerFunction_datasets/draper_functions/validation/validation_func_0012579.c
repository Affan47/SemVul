gc_db_is_activity_in_profile(GcomprisProfile *profile, char *activity_name)
{
  SUPPORT_OR_RETURN(TRUE);

#ifdef USE_SQLITE
  char *zErrMsg;
  char **result;
  int rc;
  int nrow;
  int ncolumn;
  gchar *request;

  request = g_strdup_printf(DB_IS_ACTIVITY_IN_PROFILE_ID(profile->profile_id, activity_name));

  rc = sqlite3_get_table(gcompris_db,
			 request,
			 &result,
			 &nrow,
			 &ncolumn,
			 &zErrMsg
			 );

  g_free(request);

  if( rc!=SQLITE_OK ){
    g_error("SQL error: %s\n", zErrMsg);
  }

  if (nrow == 0){

    return TRUE;
  }


  return FALSE;
#endif
}
