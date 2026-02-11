spill(Instruction *defi, Value *slot, LValue *lval)
{
   const DataType ty = typeOfSize(lval->reg.size);

   slot = offsetSlot(slot, lval);

   Instruction *st;
   if (slot->reg.file == FILE_MEMORY_LOCAL) {
      st = new_Instruction(func, OP_STORE, ty);
      st->setSrc(0, slot);
      st->setSrc(1, lval);
      lval->noSpill = 1;
   } else {
      st = new_Instruction(func, OP_CVT, ty);
      st->setDef(0, slot);
      st->setSrc(0, lval);
   }
   defi->bb->insertAfter(defi, st);
}
