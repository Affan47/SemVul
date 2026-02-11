ConvertDebugDeclareToDebugValue(DbgDeclareInst *DDI,
                                           LoadInst *LI, DIBuilder &Builder) {
  DIVariable DIVar(DDI->getVariable());
  if (!DIVar.Verify())
    return false;

  Instruction *DbgVal =
    Builder.insertDbgValueIntrinsic(LI->getOperand(0), 0,
                                    DIVar, LI);


  DebugLoc LIDL = LI->getDebugLoc();
  if (!LIDL.isUnknown())
    DbgVal->setDebugLoc(LIDL);

  else
    DbgVal->setDebugLoc(DDI->getDebugLoc());
  return true;
}
