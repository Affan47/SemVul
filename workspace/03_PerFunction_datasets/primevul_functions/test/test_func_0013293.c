void WasmBinaryBuilder::visitTryOrTryInBlock(Expression*& out) {
  BYN_TRACE("zz node: Try\n");
  auto* curr = allocator.alloc<Try>();
  startControlFlow(curr);


  curr->type = getType();
  curr->body = getBlockOrSingleton(curr->type);

  Builder builder(wasm);

  Name catchLabel = getNextLabel();
  breakStack.push_back({catchLabel, curr->type});

  auto readCatchBody = [&](Type tagType) {
    auto start = expressionStack.size();
    if (tagType != Type::none) {
      pushExpression(builder.makePop(tagType));
    }
    processExpressions();
    size_t end = expressionStack.size();
    if (start > end) {
      throwError("block cannot pop from outside");
    }
    if (end - start == 1) {
      curr->catchBodies.push_back(popExpression());
    } else {
      auto* block = allocator.alloc<Block>();
      pushBlockElements(block, curr->type, start);
      block->finalize(curr->type);
      curr->catchBodies.push_back(block);
    }
  };

  while (lastSeparator == BinaryConsts::Catch ||
         lastSeparator == BinaryConsts::CatchAll) {
    if (lastSeparator == BinaryConsts::Catch) {
      auto index = getU32LEB();
      if (index >= wasm.tags.size()) {
        throwError("bad tag index");
      }
      auto* tag = wasm.tags[index].get();
      curr->catchTags.push_back(tag->name);
      readCatchBody(tag->sig.params);

    } else {
      if (curr->hasCatchAll()) {
        throwError("there should be at most one 'catch_all' clause per try");
      }
      readCatchBody(Type::none);
    }
  }
  breakStack.pop_back();

  if (lastSeparator == BinaryConsts::Delegate) {
    curr->delegateTarget = getExceptionTargetName(getU32LEB());
  }


  curr->name = getNextLabel();
  if (auto* block = curr->body->dynCast<Block>()) {
    if (block->name.is()) {
      if (exceptionTargetNames.find(block->name) !=
          exceptionTargetNames.end()) {
        BranchUtils::replaceExceptionTargets(block, block->name, curr->name);
        exceptionTargetNames.erase(block->name);
      }
    }
  }
  if (exceptionTargetNames.find(catchLabel) != exceptionTargetNames.end()) {
    for (auto* catchBody : curr->catchBodies) {
      BranchUtils::replaceExceptionTargets(catchBody, catchLabel, curr->name);
    }
    exceptionTargetNames.erase(catchLabel);
  }


  EHUtils::handleBlockNestedPop(curr, currFunction, wasm);
  curr->finalize(curr->type);


  if (breakTargetNames.find(catchLabel) == breakTargetNames.end()) {
    out = curr;
  } else {

    auto* block = builder.makeBlock(catchLabel, curr);
    out = block;
  }
  breakTargetNames.erase(catchLabel);
}
