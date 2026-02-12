int mysql_db_reconnect(SV* h)
{
  dTHX;
  D_imp_xxh(h);
  imp_dbh_t* imp_dbh;
  MYSQL save_socket;

  if (DBIc_TYPE(imp_xxh) == DBIt_ST)
  {
    imp_dbh = (imp_dbh_t*) DBIc_PARENT_COM(imp_xxh);
    h = DBIc_PARENT_H(imp_xxh);
  }
  else
    imp_dbh= (imp_dbh_t*) imp_xxh;

  if (mysql_errno(imp_dbh->pmysql) != CR_SERVER_GONE_ERROR)

    return FALSE;

  if (!DBIc_has(imp_dbh, DBIcf_AutoCommit) || !imp_dbh->auto_reconnect)
  {


    return FALSE;
  }


  save_socket= *(imp_dbh->pmysql);
  memcpy (&save_socket, imp_dbh->pmysql,sizeof(save_socket));
  memset (imp_dbh->pmysql,0,sizeof(*(imp_dbh->pmysql)));


  if (!dbd_db_disconnect(h, imp_dbh) || !my_login(aTHX_ h, imp_dbh))
  {
    do_error(h, mysql_errno(imp_dbh->pmysql), mysql_error(imp_dbh->pmysql),
             mysql_sqlstate(imp_dbh->pmysql));
    memcpy (imp_dbh->pmysql, &save_socket, sizeof(save_socket));
    ++imp_dbh->stats.auto_reconnects_failed;
    return FALSE;
  }


  DBIc_ACTIVE_on(imp_dbh);

  ++imp_dbh->stats.auto_reconnects_ok;
  return TRUE;
}
