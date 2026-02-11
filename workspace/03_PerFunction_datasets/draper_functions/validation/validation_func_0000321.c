emitImmediatePredicate(raw_ostream &OS, ImmPredicateSet &ImmPredicates) {
    bool EmittedAnything = false;
    for (unsigned i = 0, e = Operands.size(); i != e; ++i) {
      if (!Operands[i].isImm()) continue;

      unsigned Code = Operands[i].getImmCode();
      if (Code == 0) continue;

      if (EmittedAnything)
        OS << " &&\n        ";

      TreePredicateFn PredFn = ImmPredicates.getPredicate(Code-1);


      OS << "VT == "
         << getEnumName(PredFn.getOrigPatFragRecord()->getTree(0)->getType(0))
         << " && ";


      OS << PredFn.getFnName() << "(imm" << i <<')';
      EmittedAnything = true;
    }
  }
