int JOIN::rollup_send_data(uint idx)
{
  uint i;
  for (i= send_group_parts ; i-- > idx ; )
  {
    int res= 0;

    copy_ref_ptr_array(ref_ptrs, rollup.ref_pointer_arrays[i]);
    if ((!having || having->val_int()))
    {
      if (send_records < unit->select_limit_cnt && do_send_rows &&
	  (res= result->send_data(rollup.fields[i])) > 0)
	return 1;
      if (!res)
        send_records++;
    }
  }

  set_items_ref_array(current_ref_ptrs);
  return 0;
}
