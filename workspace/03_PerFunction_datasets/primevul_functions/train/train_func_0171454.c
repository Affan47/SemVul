int ha_end()
{
  int error= 0;
  DBUG_ENTER("ha_end");


  if (unlikely(ha_finish_errors()))
    error= 1;

  DBUG_RETURN(error);
}
