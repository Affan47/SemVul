int ha_maria::index_next_same(uchar * buf,
                              const uchar *key __attribute__ ((unused)),
                              uint length __attribute__ ((unused)))
{
  int error;
  DBUG_ASSERT(inited == INDEX);
  register_handler(file);


  do
  {
    error= maria_rnext_same(file,buf);
  } while (error == HA_ERR_RECORD_DELETED);
  return error;
}
