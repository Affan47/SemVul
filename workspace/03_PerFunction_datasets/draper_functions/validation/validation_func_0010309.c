combineLoadToNewType(InstCombiner &IC, LoadInst &LI, Type *NewTy,
                                      const Twine &Suffix = "") {
  Value *Ptr = LI.getPointerOperand();
  unsigned AS = LI.getPointerAddressSpace();
  SmallVector<std::pair<unsigned, MDNode *>, 8> MD;
  LI.getAllMetadata(MD);

  LoadInst *NewLoad = IC.Builder->CreateAlignedLoad(
      IC.Builder->CreateBitCast(Ptr, NewTy->getPointerTo(AS)),
      LI.getAlignment(), LI.getName() + Suffix);
  MDBuilder MDB(NewLoad->getContext());
  for (const auto &MDPair : MD) {
    unsigned ID = MDPair.first;
    MDNode *N = MDPair.second;


    switch (ID) {
    case LLVMContext::MD_dbg:
    case LLVMContext::MD_tbaa:
    case LLVMContext::MD_prof:
    case LLVMContext::MD_fpmath:
    case LLVMContext::MD_tbaa_struct:
    case LLVMContext::MD_invariant_load:
    case LLVMContext::MD_alias_scope:
    case LLVMContext::MD_noalias:
    case LLVMContext::MD_nontemporal:
    case LLVMContext::MD_mem_parallel_loop_access:

      NewLoad->setMetadata(ID, N);
      break;

    case LLVMContext::MD_nonnull:

      if (NewTy->isPointerTy()) {
        NewLoad->setMetadata(ID, N);
        break;
      }

      if (NewTy->isIntegerTy()) {
        auto *ITy = cast<IntegerType>(NewTy);
        auto *NullInt = ConstantExpr::getPtrToInt(
            ConstantPointerNull::get(cast<PointerType>(Ptr->getType())), ITy);
        auto *NonNullInt =
            ConstantExpr::getAdd(NullInt, ConstantInt::get(ITy, 1));
        NewLoad->setMetadata(LLVMContext::MD_range,
                             MDB.createRange(NonNullInt, NullInt));
      }
      break;
    case LLVMContext::MD_align:
    case LLVMContext::MD_dereferenceable:
    case LLVMContext::MD_dereferenceable_or_null:

      if (NewTy->isPointerTy())
        NewLoad->setMetadata(ID, N);
      break;
    case LLVMContext::MD_range:


      break;
    }
  }
  return NewLoad;
}
