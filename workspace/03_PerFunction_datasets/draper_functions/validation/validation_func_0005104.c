getTLSModel(const GlobalValue *GV, Reloc::Model reloc) {
  bool isLocal = GV->hasLocalLinkage();
  bool isDeclaration = GV->isDeclaration();


  bool isHidden = GV->hasHiddenVisibility();

  if (reloc == Reloc::PIC_) {
    if (isLocal || isHidden)
      return TLSModel::LocalDynamic;
    else
      return TLSModel::GeneralDynamic;
  } else {
    if (!isDeclaration || isHidden)
      return TLSModel::LocalExec;
    else
      return TLSModel::InitialExec;
  }
}
