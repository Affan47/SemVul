printOneChild(raw_ostream &OS, Child Ptr,
                          NodeKind Kind) const {
  switch (Kind) {
  case Twine::NullKind: break;
  case Twine::EmptyKind: break;
  case Twine::TwineKind:
    Ptr.twine->print(OS);
    break;
  case Twine::CStringKind:
    OS << Ptr.cString;
    break;
  case Twine::StdStringKind:
    OS << *Ptr.stdString;
    break;
  case Twine::StringRefKind:
    OS << *Ptr.stringRef;
    break;
  case Twine::CharKind:
    OS << Ptr.character;
    break;
  case Twine::DecUIKind:
    OS << Ptr.decUI;
    break;
  case Twine::DecIKind:
    OS << Ptr.decI;
    break;
  case Twine::DecULKind:
    OS << *Ptr.decUL;
    break;
  case Twine::DecLKind:
    OS << *Ptr.decL;
    break;
  case Twine::DecULLKind:
    OS << *Ptr.decULL;
    break;
  case Twine::DecLLKind:
    OS << *Ptr.decLL;
    break;
  case Twine::UHexKind:
    OS.write_hex(*Ptr.uHex);
    break;
  }
}
