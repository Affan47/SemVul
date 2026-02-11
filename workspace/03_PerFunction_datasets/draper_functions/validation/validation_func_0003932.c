addBlockByrefAddress(const DbgVariable &DV, DIE &Die,
                                     dwarf::Attribute Attribute,
                                     const MachineLocation &Location) {
  const DIType *Ty = DV.getType();
  const DIType *TmpTy = Ty;
  uint16_t Tag = Ty->getTag();
  bool isPointer = false;

  StringRef varName = DV.getName();

  if (Tag == dwarf::DW_TAG_pointer_type) {
    auto *DTy = cast<DIDerivedType>(Ty);
    TmpTy = resolve(DTy->getBaseType());
    isPointer = true;
  }


  DINodeArray Fields = cast<DICompositeType>(TmpTy)->getElements();
  const DIDerivedType *varField = nullptr;
  const DIDerivedType *forwardingField = nullptr;

  for (unsigned i = 0, N = Fields.size(); i < N; ++i) {
    auto *DT = cast<DIDerivedType>(Fields[i]);
    StringRef fieldName = DT->getName();
    if (fieldName == "__forwarding")
      forwardingField = DT;
    else if (fieldName == varName)
      varField = DT;
  }


  unsigned forwardingFieldOffset = forwardingField->getOffsetInBits() >> 3;
  unsigned varFieldOffset = varField->getOffsetInBits() >> 2;


  DIELoc *Loc = new (DIEValueAllocator) DIELoc;

  bool validReg;
  if (Location.isReg())
    validReg = addRegisterOpPiece(*Loc, Location.getReg());
  else
    validReg = addRegisterOffset(*Loc, Location.getReg(), Location.getOffset());

  if (!validReg)
    return;


  if (isPointer)
    addUInt(*Loc, dwarf::DW_FORM_data1, dwarf::DW_OP_deref);


  if (forwardingFieldOffset > 0) {
    addUInt(*Loc, dwarf::DW_FORM_data1, dwarf::DW_OP_plus_uconst);
    addUInt(*Loc, dwarf::DW_FORM_udata, forwardingFieldOffset);
  }


  addUInt(*Loc, dwarf::DW_FORM_data1, dwarf::DW_OP_deref);


  if (varFieldOffset > 0) {
    addUInt(*Loc, dwarf::DW_FORM_data1, dwarf::DW_OP_plus_uconst);
    addUInt(*Loc, dwarf::DW_FORM_udata, varFieldOffset);
  }


  addBlock(Die, Attribute, Loc);
}
