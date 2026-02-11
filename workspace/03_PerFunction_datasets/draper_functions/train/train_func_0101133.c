intern_dyn_info (unw_addr_space_t as, unw_accessors_t *a,
		 unw_word_t *addr, unw_dyn_info_t *di, void *arg)
{
  unw_word_t first_region;
  int ret;

  switch (di->format)
    {
    case UNW_INFO_FORMAT_DYNAMIC:
      if ((ret = fetchw (as, a, addr, &di->u.pi.name_ptr, arg)) < 0
	  || (ret = fetchw (as, a, addr, &di->u.pi.handler, arg)) < 0
	  || (ret = fetch32 (as, a, addr,
			     (int32_t *) &di->u.pi.flags, arg)) < 0)
	goto out;
      *addr += 4;
      if ((ret = fetchw (as, a, addr, &first_region, arg)) < 0
	  || (ret = intern_regions (as, a, &first_region, &di->u.pi.regions,
				    arg)) < 0)
	goto out;
      break;

    case UNW_INFO_FORMAT_TABLE:
      if ((ret = fetchw (as, a, addr, &di->u.ti.name_ptr, arg)) < 0
	  || (ret = fetchw (as, a, addr, &di->u.ti.segbase, arg)) < 0
	  || (ret = fetchw (as, a, addr, &di->u.ti.table_len, arg)) < 0
	  || (ret = intern_array (as, a, addr, di->u.ti.table_len,
				  &di->u.ti.table_data, arg)) < 0)
	goto out;
      break;

    case UNW_INFO_FORMAT_REMOTE_TABLE:
      if ((ret = fetchw (as, a, addr, &di->u.rti.name_ptr, arg)) < 0
	  || (ret = fetchw (as, a, addr, &di->u.rti.segbase, arg)) < 0
	  || (ret = fetchw (as, a, addr, &di->u.rti.table_len, arg)) < 0
	  || (ret = fetchw (as, a, addr, &di->u.rti.table_data, arg)) < 0)
	goto out;
      break;

    default:
      ret = -UNW_ENOINFO;
      goto out;
    }
  return 0;

 out:
  free_dyn_info (di);
  return ret;
}
