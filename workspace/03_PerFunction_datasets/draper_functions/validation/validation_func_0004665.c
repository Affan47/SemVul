vect_get_data_access_cost (struct data_reference *dr,
                           unsigned int *inside_cost,
                           unsigned int *outside_cost)
{
  gimple stmt = DR_STMT (dr);
  stmt_vec_info stmt_info = vinfo_for_stmt (stmt);
  int nunits = TYPE_VECTOR_SUBPARTS (STMT_VINFO_VECTYPE (stmt_info));
  loop_vec_info loop_vinfo = STMT_VINFO_LOOP_VINFO (stmt_info);
  int vf = LOOP_VINFO_VECT_FACTOR (loop_vinfo);
  int ncopies = vf / nunits;
  bool supportable_dr_alignment = vect_supportable_dr_alignment (dr, true);

  if (!supportable_dr_alignment)
    *inside_cost = VECT_MAX_COST;
  else
    {
      if (DR_IS_READ (dr))
        vect_get_load_cost (dr, ncopies, true, inside_cost, outside_cost);
      else
        vect_get_store_cost (dr, ncopies, inside_cost);
    }

  if (vect_print_dump_info (REPORT_COST))
    fprintf (vect_dump, "vect_get_data_access_cost: inside_cost = %d, "
             "outside_cost = %d.", *inside_cost, *outside_cost);
}
