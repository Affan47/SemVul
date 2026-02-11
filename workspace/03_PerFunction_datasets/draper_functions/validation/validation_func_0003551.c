dd_initialize(pTHX) {
  static int initialized = 0;
  if (!initialized) {
    initialized = 1;
#if DD_GROW_VIA_BLOCKHOOK
    {
      static BHK bhk;
#if PERL_VERSION_GE(5,13,6)
      BhkENTRY_set(&bhk, bhk_start, dd_block_start);
#else
      BhkENTRY_set(&bhk, start, dd_block_start);
#endif
      Perl_blockhook_register(aTHX_ &bhk);
    }
#else
    hook_op_check(OP_ENTEREVAL, dd_ck_entereval, NULL);
#endif
    hook_op_check(OP_RV2CV, dd_ck_rv2cv, NULL);
#if !DD_CONST_VIA_RV2CV
    hook_op_check(OP_CONST, dd_ck_const, NULL);
#endif
  }
}
