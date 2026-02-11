ann2icl(AST::Node* ann) {
    if (ann) {
      if (ann->hasAtom("val"))
        return ICL_VAL;
      if (ann->hasAtom("domain"))
        return ICL_DOM;
      if (ann->hasAtom("bounds") ||
          ann->hasAtom("boundsR") ||
          ann->hasAtom("boundsD") ||
          ann->hasAtom("boundsZ"))
        return ICL_BND;
    }
    return ICL_DEF;
  }
