void WasmBinaryBuilder::visitLet(Block* curr) {


  startControlFlow(curr);

  curr->type = getType();


  requireFunctionContext("let");
  Index absoluteStart = currFunction->vars.size();
  readVars();
  Index numNewVars = currFunction->vars.size() - absoluteStart;

  Builder builder(wasm);
  for (Index i = 0; i < numNewVars; i++) {
    auto* value = popNonVoidExpression();
    curr->list.push_back(builder.makeLocalSet(absoluteStart + i, value));
  }

  letStack.emplace_back(LetData{numNewVars, absoluteStart});
  curr->list.push_back(getBlockOrSingleton(curr->type));
  letStack.pop_back();
  curr->finalize(curr->type);
}
