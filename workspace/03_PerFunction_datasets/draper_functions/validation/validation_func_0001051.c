new_stmt_vec_info (gimple stmt, loop_vec_info loop_vinfo,
                   bb_vec_info bb_vinfo)
{
  stmt_vec_info res;
  res = (stmt_vec_info) xcalloc (1, sizeof (struct _stmt_vec_info));

  STMT_VINFO_TYPE (res) = undef_vec_info_type;
  STMT_VINFO_STMT (res) = stmt;
  STMT_VINFO_LOOP_VINFO (res) = loop_vinfo;
  STMT_VINFO_BB_VINFO (res) = bb_vinfo;
  STMT_VINFO_RELEVANT (res) = vect_unused_in_scope;
  STMT_VINFO_LIVE_P (res) = false;
  STMT_VINFO_VECTYPE (res) = NULL;
  STMT_VINFO_VEC_STMT (res) = NULL;
  STMT_VINFO_VECTORIZABLE (res) = true;
  STMT_VINFO_IN_PATTERN_P (res) = false;
  STMT_VINFO_RELATED_STMT (res) = NULL;
  STMT_VINFO_PATTERN_DEF_SEQ (res) = NULL;
  STMT_VINFO_DATA_REF (res) = NULL;

  STMT_VINFO_DR_BASE_ADDRESS (res) = NULL;
  STMT_VINFO_DR_OFFSET (res) = NULL;
  STMT_VINFO_DR_INIT (res) = NULL;
  STMT_VINFO_DR_STEP (res) = NULL;
  STMT_VINFO_DR_ALIGNED_TO (res) = NULL;

  if (gimple_code (stmt) == GIMPLE_PHI
      && is_loop_header_bb_p (gimple_bb (stmt)))
    STMT_VINFO_DEF_TYPE (res) = vect_unknown_def_type;
  else
    STMT_VINFO_DEF_TYPE (res) = vect_internal_def;

  STMT_VINFO_SAME_ALIGN_REFS (res) = NULL;
  STMT_VINFO_INSIDE_OF_LOOP_COST (res) = 0;
  STMT_VINFO_OUTSIDE_OF_LOOP_COST (res) = 0;
  STMT_SLP_TYPE (res) = loop_vect;
  GROUP_FIRST_ELEMENT (res) = NULL;
  GROUP_NEXT_ELEMENT (res) = NULL;
  GROUP_SIZE (res) = 0;
  GROUP_STORE_COUNT (res) = 0;
  GROUP_GAP (res) = 0;
  GROUP_SAME_DR_STMT (res) = NULL;
  GROUP_READ_WRITE_DEPENDENCE (res) = false;

  return res;
}
