allocated_mark (SCM cell)
{
  unsigned long int cell_segment = scm_i_find_heap_segment_containing_object (cell);
  unsigned int span = scm_i_heap_segment_table[cell_segment]->span;
  unsigned int i;

  for (i = 1; i != span * 2; ++i)
    {
      SCM obj = SCM_CELL_OBJECT (cell, i);
      long int obj_segment = scm_i_find_heap_segment_containing_object (obj);
      if (obj_segment >= 0)
	scm_gc_mark (obj);
    }
  return SCM_BOOL_F;
}
