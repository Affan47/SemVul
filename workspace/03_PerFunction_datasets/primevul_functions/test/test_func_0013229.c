void WasmBinaryBuilder::visitCallIndirect(CallIndirect* curr) {
  BYN_TRACE("zz node: CallIndirect\n");
  auto index = getU32LEB();
  curr->heapType = getTypeByIndex(index);
  Index tableIdx = getU32LEB();

  auto num = curr->heapType.getSignature().params.size();
  curr->operands.resize(num);
  curr->target = popNonVoidExpression();
  for (size_t i = 0; i < num; i++) {
    curr->operands[num - i - 1] = popNonVoidExpression();
  }

  tableRefs[tableIdx].push_back(curr);
  curr->finalize();
}
