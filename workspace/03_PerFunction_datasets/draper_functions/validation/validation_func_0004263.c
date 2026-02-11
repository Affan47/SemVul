vect_can_force_dr_alignment_p (const_tree decl, unsigned int alignment)
{
  if (TREE_CODE (decl) != VAR_DECL)
    return false;

  if (DECL_EXTERNAL (decl))
    return false;

  if (TREE_ASM_WRITTEN (decl))
    return false;


  if (DECL_SECTION_NAME (decl) != NULL_TREE
      && !DECL_HAS_IMPLICIT_SECTION_NAME_P (decl))
    return false;

  if (TREE_STATIC (decl))
    return (alignment <= MAX_OFILE_ALIGNMENT);
  else
    return (alignment <= MAX_STACK_ALIGNMENT);
}
