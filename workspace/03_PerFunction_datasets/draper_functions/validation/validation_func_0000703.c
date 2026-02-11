vect_get_loop_based_defs (tree *oprnd, gimple stmt, enum vect_def_type dt,
			  vec<tree> *vec_oprnds, int multi_step_cvt)
{
  tree vec_oprnd;


  if (TREE_CODE (TREE_TYPE (*oprnd)) != VECTOR_TYPE)
    vec_oprnd = vect_get_vec_def_for_operand (*oprnd, stmt, NULL);
  else
    vec_oprnd = vect_get_vec_def_for_stmt_copy (dt, *oprnd);

  vec_oprnds->quick_push (vec_oprnd);


  vec_oprnd = vect_get_vec_def_for_stmt_copy (dt, vec_oprnd);
  vec_oprnds->quick_push (vec_oprnd);

  *oprnd = vec_oprnd;


  if (multi_step_cvt)
    vect_get_loop_based_defs (oprnd, stmt, dt, vec_oprnds,  multi_step_cvt - 1);
}
