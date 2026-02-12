int ha_enable_transaction(THD *thd, bool on)
{
  int error=0;
  DBUG_ENTER("ha_enable_transaction");
  DBUG_PRINT("enter", ("on: %d", (int) on));

  if ((thd->transaction.on= on))
  {


    if (likely(!(error= ha_commit_trans(thd, 0))))
      error= trans_commit_implicit(thd);
  }
  DBUG_RETURN(error);
}
