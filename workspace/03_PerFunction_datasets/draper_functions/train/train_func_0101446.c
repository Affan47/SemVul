pkeq_closure(ap_manager_t* man, bool destructive, pkeq_t* a)
{
  return destructive ? a : pk_copy(man,a);
}
