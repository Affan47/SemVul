static SLJIT_INLINE void check_start_used_ptr(compiler_common *common)
{

DEFINE_COMPILER;
struct sljit_jump *jump;

if (common->mode == PCRE2_JIT_PARTIAL_SOFT)
  {

  OP2(SLJIT_ADD, TMP1, 0, SLJIT_MEM1(SLJIT_SP), common->start_used_ptr, SLJIT_IMM, 1);


  jump = CMP(SLJIT_LESS_EQUAL, TMP1, 0, STR_PTR, 0);
  OP1(SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), common->start_used_ptr, STR_PTR, 0);
  JUMPHERE(jump);
  }
else if (common->mode == PCRE2_JIT_PARTIAL_HARD)
  {
  jump = CMP(SLJIT_LESS_EQUAL, SLJIT_MEM1(SLJIT_SP), common->start_used_ptr, STR_PTR, 0);
  OP1(SLJIT_MOV, SLJIT_MEM1(SLJIT_SP), common->start_used_ptr, STR_PTR, 0);
  JUMPHERE(jump);
  }
}
