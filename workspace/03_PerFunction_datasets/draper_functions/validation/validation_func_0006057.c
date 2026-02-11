safeCxtI(const Value *V, const Instruction *CxtI) {


  if (CxtI && CxtI->getParent())
    return CxtI;


  CxtI = dyn_cast<Instruction>(V);
  if (CxtI && CxtI->getParent())
    return CxtI;

  return nullptr;
}
