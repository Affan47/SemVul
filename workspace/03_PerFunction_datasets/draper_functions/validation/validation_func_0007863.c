ParseExtractValue(Instruction *&Inst, PerFunctionState &PFS) {
  Value *Val; LocTy Loc;
  SmallVector<unsigned, 4> Indices;
  bool AteExtraComma;
  if (ParseTypeAndValue(Val, Loc, PFS) ||
      ParseIndexList(Indices, AteExtraComma))
    return true;

  if (!Val->getType()->isAggregateType())
    return Error(Loc, "extractvalue operand must be aggregate type");

  if (!ExtractValueInst::getIndexedType(Val->getType(), Indices))
    return Error(Loc, "invalid indices for extractvalue");
  Inst = ExtractValueInst::Create(Val, Indices);
  return AteExtraComma ? InstExtraComma : InstNormal;
}
