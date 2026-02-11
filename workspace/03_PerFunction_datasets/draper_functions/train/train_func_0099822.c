calcDelay(const Instruction *insn, int cycle) const
{
   int delay = 0, ready = cycle;

   for (int s = 0; insn->srcExists(s); ++s)
      checkRd(insn->getSrc(s), cycle, delay);


   switch (Target::getOpClass(insn->op)) {
   case OPCLASS_SFU:
      ready = score->res.sfu;
      break;
   case OPCLASS_ARITH:
      if (insn->op == OP_MUL && !isFloatType(insn->dType))
         ready = score->res.imul;
      break;
   case OPCLASS_TEXTURE:
      ready = score->res.tex;
      break;
   case OPCLASS_LOAD:
      ready = score->res.ld[insn->src(0).getFile()];
      break;
   case OPCLASS_STORE:
      ready = score->res.st[insn->src(0).getFile()];
      break;
   default:
      break;
   }
   if (Target::getOpClass(insn->op) != OPCLASS_TEXTURE)
      ready = MAX2(ready, score->res.tex);

   delay = MAX2(delay, ready - cycle);


   return MIN2(delay - 1, NVE4_MAX_ISSUE_DELAY);
}
