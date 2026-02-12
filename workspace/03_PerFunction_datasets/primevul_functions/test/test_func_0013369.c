void WasmBinaryBuilder::visitRethrow(Rethrow* curr) {
  BYN_TRACE("zz node: Rethrow\n");
  curr->target = getExceptionTargetName(getU32LEB());

  if (curr->target == DELEGATE_CALLER_TARGET) {
    throwError(std::string("rethrow target cannot use internal name ") +
               DELEGATE_CALLER_TARGET.str);
  }
  curr->finalize();
}
