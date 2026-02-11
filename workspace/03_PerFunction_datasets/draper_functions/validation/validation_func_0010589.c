RecordScatteredRelocation(const MCAssembler &Asm,
                                 const MCAsmLayout &Layout,
                                 const MCFragment *Fragment,
                                 const MCFixup &Fixup, MCValue Target,
                                 uint64_t &FixedValue) {
    uint32_t FixupOffset = Layout.getFragmentOffset(Fragment)+Fixup.getOffset();
    unsigned IsPCRel = isFixupKindPCRel(Fixup.getKind());
    unsigned Log2Size = getFixupKindLog2Size(Fixup.getKind());
    unsigned Type = RIT_Vanilla;


    const MCSymbol *A = &Target.getSymA()->getSymbol();
    MCSymbolData *A_SD = &Asm.getSymbolData(*A);

    if (!A_SD->getFragment())
      report_fatal_error("symbol '" + A->getName() +
                        "' can not be undefined in a subtraction expression");

    uint32_t Value = Layout.getSymbolAddress(A_SD);
    uint32_t Value2 = 0;

    if (const MCSymbolRefExpr *B = Target.getSymB()) {
      MCSymbolData *B_SD = &Asm.getSymbolData(B->getSymbol());

      if (!B_SD->getFragment())
        report_fatal_error("symbol '" + B->getSymbol().getName() +
                          "' can not be undefined in a subtraction expression");


      Type = A_SD->isExternal() ? RIT_Difference : RIT_LocalDifference;
      Value2 = Layout.getSymbolAddress(B_SD);
    }


    if (Type == RIT_Difference || Type == RIT_LocalDifference) {
      MachRelocationEntry MRE;
      MRE.Word0 = ((0         <<  0) |
                   (RIT_Pair  << 24) |
                   (Log2Size  << 28) |
                   (IsPCRel   << 30) |
                   RF_Scattered);
      MRE.Word1 = Value2;
      Relocations[Fragment->getParent()].push_back(MRE);
    }

    MachRelocationEntry MRE;
    MRE.Word0 = ((FixupOffset <<  0) |
                 (Type        << 24) |
                 (Log2Size    << 28) |
                 (IsPCRel     << 30) |
                 RF_Scattered);
    MRE.Word1 = Value;
    Relocations[Fragment->getParent()].push_back(MRE);
  }
