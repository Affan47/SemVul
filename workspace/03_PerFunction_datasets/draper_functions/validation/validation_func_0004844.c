maybe_assemble_visibility (decl)
     tree decl;
{
  enum symbol_visibility vis = decl_visibility (decl);

  if (vis != VISIBILITY_DEFAULT)
    (* targetm.asm_out.visibility) (decl, vis);
}
