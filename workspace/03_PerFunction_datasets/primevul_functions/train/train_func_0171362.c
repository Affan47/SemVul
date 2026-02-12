int subselect_hash_sj_engine::prepare(THD *thd_arg)
{


  set_thd(thd_arg);
  return materialize_engine->prepare(thd);
}
