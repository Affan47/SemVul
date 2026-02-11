EmitStrNLen(Value *Ptr, Value *MaxLen, IRBuilder<> &B,
                         const DataLayout &DL, const TargetLibraryInfo *TLI) {
  if (!TLI->has(LibFunc::strnlen))
    return nullptr;

  Module *M = B.GetInsertBlock()->getParent()->getParent();
  AttributeSet AS[2];
  AS[0] = AttributeSet::get(M->getContext(), 1, Attribute::NoCapture);
  Attribute::AttrKind AVs[2] = { Attribute::ReadOnly, Attribute::NoUnwind };
  AS[1] = AttributeSet::get(M->getContext(), AttributeSet::FunctionIndex, AVs);

  LLVMContext &Context = B.GetInsertBlock()->getContext();
  Constant *StrNLen =
      M->getOrInsertFunction("strnlen", AttributeSet::get(M->getContext(), AS),
                             DL.getIntPtrType(Context), B.getInt8PtrTy(),
                             DL.getIntPtrType(Context), nullptr);
  CallInst *CI = B.CreateCall(StrNLen, {CastToCStr(Ptr, B), MaxLen}, "strnlen");
  if (const Function *F = dyn_cast<Function>(StrNLen->stripPointerCasts()))
    CI->setCallingConv(F->getCallingConv());

  return CI;
}
