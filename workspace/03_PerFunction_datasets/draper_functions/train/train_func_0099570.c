getCodeAddrSpace(MemSDNode *N) {
  const Value *Src = N->getMemOperand()->getValue();

  if (!Src)
    return NVPTX::PTXLdStInstCode::GENERIC;

  if (auto *PT = dyn_cast<PointerType>(Src->getType())) {
    switch (PT->getAddressSpace()) {
    case llvm::ADDRESS_SPACE_LOCAL: return NVPTX::PTXLdStInstCode::LOCAL;
    case llvm::ADDRESS_SPACE_GLOBAL: return NVPTX::PTXLdStInstCode::GLOBAL;
    case llvm::ADDRESS_SPACE_SHARED: return NVPTX::PTXLdStInstCode::SHARED;
    case llvm::ADDRESS_SPACE_GENERIC: return NVPTX::PTXLdStInstCode::GENERIC;
    case llvm::ADDRESS_SPACE_PARAM: return NVPTX::PTXLdStInstCode::PARAM;
    case llvm::ADDRESS_SPACE_CONST: return NVPTX::PTXLdStInstCode::CONSTANT;
    default: break;
    }
  }
  return NVPTX::PTXLdStInstCode::GENERIC;
}
