visit(BasicBlock *bb)
{
   TexInstruction *tex;
   Instruction *next;
   int s, size;

   targ = bb->getProgram()->getTarget();

   for (Instruction *i = bb->getEntry(); i; i = next) {
      next = i->next;

      if ((tex = i->asTex())) {
         switch (targ->getChipset() & ~0xf) {
         case 0x50:
         case 0x80:
         case 0x90:
         case 0xa0:
            texConstraintNV50(tex);
            break;
         case 0xc0:
         case 0xd0:
            texConstraintNVC0(tex);
            break;
         case 0xe0:
         case 0xf0:
         case 0x100:
            texConstraintNVE0(tex);
            break;
         default:
            break;
         }
      } else
      if (i->op == OP_EXPORT || i->op == OP_STORE) {
         for (size = typeSizeof(i->dType), s = 1; size > 0; ++s) {
            assert(i->srcExists(s));
            size -= i->getSrc(s)->reg.size;
         }
         condenseSrcs(i, 1, s - 1);
      } else
      if (i->op == OP_LOAD || i->op == OP_VFETCH) {
         condenseDefs(i);
         if (i->src(0).isIndirect(0) && typeSizeof(i->dType) >= 8)
            addHazard(i, i->src(0).getIndirect(0));
      } else
      if (i->op == OP_UNION ||
          i->op == OP_MERGE ||
          i->op == OP_SPLIT) {
         constrList.push_back(i);
      }
   }
   return true;
}
