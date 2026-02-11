ref_indep_loop_p_1 (struct loop *loop, mem_ref_p ref)
{
  bitmap clobbers, refs_to_check, refs;
  unsigned i;
  bitmap_iterator bi;
  bool ret = true, stored = bitmap_bit_p (ref->stored, loop->num);
  htab_t map;
  mem_ref_p aref;


  clobbers = VEC_index (bitmap, memory_accesses.clobbered_vops, loop->num);
  if (bitmap_intersect_p (ref->vops, clobbers))
    return false;

  refs_to_check = BITMAP_ALLOC (NULL);

  map = VEC_index (htab_t, memory_accesses.vop_ref_map, loop->num);
  EXECUTE_IF_AND_COMPL_IN_BITMAP (ref->vops, clobbers, 0, i, bi)
    {
      if (stored)
	refs = get_vop_accesses (map, i);
      else
	refs = get_vop_stores (map, i);

      bitmap_ior_into (refs_to_check, refs);
    }

  EXECUTE_IF_SET_IN_BITMAP (refs_to_check, 0, i, bi)
    {
      aref = VEC_index (mem_ref_p, memory_accesses.refs_list, i);
      if (!refs_independent_p (ref, aref))
	{
	  ret = false;
	  record_indep_loop (loop, aref, false);
	  break;
	}
    }

  BITMAP_FREE (refs_to_check);
  return ret;
}
