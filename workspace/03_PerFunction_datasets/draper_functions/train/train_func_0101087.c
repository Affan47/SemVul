EmitCallingConv(Record *CC, raw_ostream &O) {
  ListInit *CCActions = CC->getValueAsListInit("Actions");
  Counter = 0;

  O << "\n\nstatic bool " << CC->getName()
    << "(unsigned ValNo, MVT ValVT,\n"
    << std::string(CC->getName().size()+13, ' ')
    << "MVT LocVT, CCValAssign::LocInfo LocInfo,\n"
    << std::string(CC->getName().size()+13, ' ')
    << "ISD::ArgFlagsTy ArgFlags, CCState &State) {\n";

  for (unsigned i = 0, e = CCActions->getSize(); i != e; ++i) {
    O << "\n";
    EmitAction(CCActions->getElementAsRecord(i), 2, O);
  }

  O << "\n  return true;  // CC didn't match.\n";
  O << "}\n";
}
