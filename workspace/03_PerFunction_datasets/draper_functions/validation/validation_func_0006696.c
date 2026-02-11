FindAllocaDbgDeclare(Value *V) {
  if (MDNode *DebugNode = MDNode::getIfExists(V->getContext(), &V, 1))
    for (Value::use_iterator UI = DebugNode->use_begin(),
         E = DebugNode->use_end(); UI != E; ++UI)
      if (DbgDeclareInst *DDI = dyn_cast<DbgDeclareInst>(*UI))
        return DDI;

  return 0;
}
