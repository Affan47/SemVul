void WasmBinaryBuilder::pushExpression(Expression* curr) {
  auto type = curr->type;
  if (type.isTuple()) {

    Builder builder(wasm);


    std::vector<Type> finalTypes;
    if (!wasm.features.hasGCNNLocals()) {
      for (auto t : type) {
        if (t.isNonNullable()) {
          t = Type(t.getHeapType(), Nullable);
        }
        finalTypes.push_back(t);
      }
    }
    auto nullableType = Type(Tuple(finalTypes));
    requireFunctionContext("pushExpression-tuple");
    Index tuple = builder.addVar(currFunction, nullableType);
    expressionStack.push_back(builder.makeLocalSet(tuple, curr));
    for (Index i = 0; i < nullableType.size(); ++i) {
      Expression* value =
        builder.makeTupleExtract(builder.makeLocalGet(tuple, nullableType), i);
      if (nullableType[i] != type[i]) {

        value = builder.makeRefAs(RefAsNonNull, value);
      }
      expressionStack.push_back(value);
    }
  } else {
    expressionStack.push_back(curr);
  }
}
