void WasmBinaryBuilder::visitCallRef(CallRef* curr) {
  BYN_TRACE("zz node: CallRef\n");
  curr->target = popNonVoidExpression();
  auto type = curr->target->type;
  if (type == Type::unreachable) {


    curr->finalize(type);
    return;
  }
  if (!type.isRef()) {
    throwError("Non-ref type for a call_ref: " + type.toString());
  }
  auto heapType = type.getHeapType();
  if (!heapType.isSignature()) {
    throwError("Invalid reference type for a call_ref: " + type.toString());
  }
  auto sig = heapType.getSignature();
  auto num = sig.params.size();
  curr->operands.resize(num);
  for (size_t i = 0; i < num; i++) {
    curr->operands[num - i - 1] = popNonVoidExpression();
  }
  curr->finalize(sig.results);
}
