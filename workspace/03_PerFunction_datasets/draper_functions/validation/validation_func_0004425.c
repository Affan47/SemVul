LLVMAddCFGSimplificationPass(LLVMPassManagerRef PM) {
  unwrap(PM)->add(createCFGSimplificationPass());
}
