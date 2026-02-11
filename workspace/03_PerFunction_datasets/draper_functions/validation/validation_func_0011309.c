rollup_send_data(uint idx)
{
  uint i;
  for (i= send_group_parts ; i-- > idx ; )
  {

    memcpy((char*) ref_pointer_array,
	   (char*) rollup.ref_pointer_arrays[i],
	   ref_pointer_array_size);
    if ((!having || having->val_int()))
    {
      if (send_records < unit->select_limit_cnt && do_send_rows &&
	  result->send_data(rollup.fields[i]))
	return 1;
      send_records++;
    }
  }

  set_items_ref_array(current_ref_pointer_array);
  return 0;
}
