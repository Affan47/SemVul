gen_inlined_subroutine_die (stmt, context_die, depth)
     tree stmt;
     dw_die_ref context_die;
     int depth;
{
  tree decl = block_ultimate_origin (stmt);


  dwarf2out_abstract_function (decl);

  if (! BLOCK_ABSTRACT (stmt))
    {
      dw_die_ref subr_die
	= new_die (DW_TAG_inlined_subroutine, context_die, stmt);
      char label[MAX_ARTIFICIAL_LABEL_BYTES];

      add_abstract_origin_attribute (subr_die, decl);
      ASM_GENERATE_INTERNAL_LABEL (label, BLOCK_BEGIN_LABEL,
				   BLOCK_NUMBER (stmt));
      add_AT_lbl_id (subr_die, DW_AT_low_pc, label);
      ASM_GENERATE_INTERNAL_LABEL (label, BLOCK_END_LABEL,
				   BLOCK_NUMBER (stmt));
      add_AT_lbl_id (subr_die, DW_AT_high_pc, label);
      decls_for_scope (stmt, subr_die, depth);
      current_function_has_inlines = 1;
    }
  else


    gen_lexical_block_die (stmt, context_die, depth);
}
