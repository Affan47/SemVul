assemble_end_function (tree decl, const char *fnname ATTRIBUTE_UNUSED)
{
#ifdef ASM_DECLARE_FUNCTION_SIZE

  if (flag_reorder_blocks_and_partition)
    switch_to_section (function_section (decl));
  ASM_DECLARE_FUNCTION_SIZE (asm_out_file, fnname, decl);
#endif
  if (! CONSTANT_POOL_BEFORE_FUNCTION)
    {
      output_constant_pool (fnname, decl);
      switch_to_section (function_section (decl));
    }


  if (flag_reorder_blocks_and_partition)
    {
      section *save_text_section;

      save_text_section = in_section;
      switch_to_section (unlikely_text_section ());
      ASM_OUTPUT_LABEL (asm_out_file, crtl->subsections.cold_section_end_label);
      if (first_function_block_is_cold)
	switch_to_section (text_section);
      else
	switch_to_section (function_section (decl));
      ASM_OUTPUT_LABEL (asm_out_file, crtl->subsections.hot_section_end_label);
      switch_to_section (save_text_section);
    }
}
