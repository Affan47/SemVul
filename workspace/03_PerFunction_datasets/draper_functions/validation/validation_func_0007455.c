check_define_type(pTHX_ SourcifyConfig *pSC, SV *str, TypeSpec *pTS)
{
  u_32 flags = pTS->tflags;

  CT_DEBUG(MAIN, (XSCLASS "::check_define_type( pTS=(tflags=0x%08lX, ptr=%p) )",
                  (unsigned long) pTS->tflags, pTS->ptr));

  if (flags & T_TYPE)
  {
    Typedef *pTypedef= (Typedef *) pTS->ptr;

    while (!pTypedef->pDecl->pointer_flag && pTypedef->pType->tflags & T_TYPE)
      pTypedef = (Typedef *) pTypedef->pType->ptr;

    if (pTypedef->pDecl->pointer_flag)
      return;

    pTS   = pTypedef->pType;
    flags = pTS->tflags;
  }

  if (flags & T_ENUM)
  {
    EnumSpecifier *pES = (EnumSpecifier *) pTS->ptr;

    if (pES && (pES->tflags & T_ALREADY_DUMPED) == 0)
      add_enum_spec_string(aTHX_ pSC, str, pES);
  }
  else if (flags & T_COMPOUND)
  {
    Struct *pStruct = (Struct *) pTS->ptr;

    if (pStruct && (pStruct->tflags & T_ALREADY_DUMPED) == 0)
      add_struct_spec_string(aTHX_ pSC, str, pStruct);
  }
}
