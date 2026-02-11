getELFComdat(const GlobalValue *GV) {
  const Comdat *C = GV->getComdat();
  if (!C)
    return nullptr;

  if (C->getSelectionKind() != Comdat::Any)
    report_fatal_error("ELF COMDATs only support SelectionKind::Any, '" +
                       C->getName() + "' cannot be lowered.");

  return C;
}
