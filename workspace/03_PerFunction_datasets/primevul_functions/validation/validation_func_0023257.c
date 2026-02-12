void purge_tables(bool purge_flag)
{


  kill_delayed_threads();


  tc_purge(purge_flag);

  tdc_purge(true);
}
