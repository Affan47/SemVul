vect_find_same_alignment_drs (struct data_dependence_relation *ddr,
			      loop_vec_info loop_vinfo)
{
  unsigned int i;
  struct loop *loop = LOOP_VINFO_LOOP (loop_vinfo);
  int vectorization_factor = LOOP_VINFO_VECT_FACTOR (loop_vinfo);
  struct data_reference *dra = DDR_A (ddr);
  struct data_reference *drb = DDR_B (ddr);
  stmt_vec_info stmtinfo_a = vinfo_for_stmt (DR_STMT (dra));
  stmt_vec_info stmtinfo_b = vinfo_for_stmt (DR_STMT (drb));
  int dra_size = GET_MODE_SIZE (TYPE_MODE (TREE_TYPE (DR_REF (dra))));
  int drb_size = GET_MODE_SIZE (TYPE_MODE (TREE_TYPE (DR_REF (drb))));
  lambda_vector dist_v;
  unsigned int loop_depth;

  if (DDR_ARE_DEPENDENT (ddr) == chrec_known)
    return;

  if (dra == drb)
    return;

  if (DDR_ARE_DEPENDENT (ddr) == chrec_dont_know)
    return;


  if (DDR_NUM_DIST_VECTS (ddr) == 0)
    return;


  if (!operand_equal_p (DR_STEP (dra), DR_STEP (drb), 0))
    return;

  loop_depth = index_in_loop_nest (loop->num, DDR_LOOP_NEST (ddr));
  FOR_EACH_VEC_ELT (DDR_DIST_VECTS (ddr), i, dist_v)
    {
      int dist = dist_v[loop_depth];

      if (dump_enabled_p ())
	dump_printf_loc (MSG_NOTE, vect_location,
                         "dependence distance  = %d.", dist);


      if (dist == 0
	  || (dist % vectorization_factor == 0 && dra_size == drb_size))
	{

	  STMT_VINFO_SAME_ALIGN_REFS (stmtinfo_a).safe_push (drb);
	  STMT_VINFO_SAME_ALIGN_REFS (stmtinfo_b).safe_push (dra);
	  if (dump_enabled_p ())
	    {
              dump_printf_loc (MSG_NOTE, vect_location,
                               "accesses have the same alignment.");
	      dump_printf (MSG_NOTE,
                           "dependence distance modulo vf == 0 between ");
	      dump_generic_expr (MSG_NOTE, TDF_SLIM, DR_REF (dra));
	      dump_printf (MSG_NOTE,  " and ");
	      dump_generic_expr (MSG_NOTE, TDF_SLIM, DR_REF (drb));
	    }
	}
    }
}
