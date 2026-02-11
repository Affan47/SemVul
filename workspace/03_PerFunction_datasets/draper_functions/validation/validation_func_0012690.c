set_in_out(IO_mt_tmp *apt, IO_mt_tmp *vpt)
{
  Block_var_table *pt;
  int i;
  IO_mt_tmp  *tmp;

  pt = alloc_block_var_table();
  construct_IntSet(pt->array_bv, a_size + 1);
  construct_IntSet(pt->scalar_bv, v_size + 1);

  for(tmp = apt, i = 0; tmp != NULL; tmp = tmp->next)
    i++;
  pt->array_mt_io_num = i;
  if(i > 0){
    pt->array_mt_io = alloc_io_mt_table(i);
    for(tmp = apt, i = 0; tmp != NULL; tmp = tmp->next, i++){
      pt->array_mt_io[i].mt_num = tmp->mt_num;
      pt->array_mt_io[i].entry_bv = tmp->entry_bv;
    }
    for(i=0; i<pt->array_mt_io_num; i++){
      if(pt->array_mt_io[i].entry_bv != NULL){
	or_IntSet(pt->array_bv,pt->array_bv,
		  pt->array_mt_io[i].entry_bv);
      }
    }
    free_io_mt_tmp(apt);
  }

  for(tmp = vpt, i = 0; tmp != NULL; tmp = tmp->next)
    i++;
  pt->scalar_mt_io_num = i;
  if(i > 0){
    pt->scalar_mt_io = alloc_io_mt_table(i);
    for(tmp = vpt, i = 0; tmp != NULL; tmp = tmp->next, i++){
      pt->scalar_mt_io[i].mt_num = tmp->mt_num;
      pt->scalar_mt_io[i].entry_bv = tmp->entry_bv;
    }
    for(i=0; i<pt->scalar_mt_io_num; i++){
      if(pt->scalar_mt_io[i].entry_bv != NULL){
	or_IntSet(pt->scalar_bv,pt->scalar_bv,
		  pt->scalar_mt_io[i].entry_bv);
      }
    }
    free_io_mt_tmp(vpt);
  }

  return pt;
}
