dumpAccessGroup(PDB_MemberAccess Access,
                                           const SymbolGroup &Group) {
  if (Group.Functions.empty() && Group.Data.empty() && Group.Unknown.empty())
    return 0;

  int Count = 0;
  if (Access == PDB_MemberAccess::Private) {
    Printer.NewLine();
    WithColor(Printer, PDB_ColorItem::Keyword).get() << "private";
    Printer << ":";
  } else if (Access == PDB_MemberAccess::Protected) {
    Printer.NewLine();
    WithColor(Printer, PDB_ColorItem::Keyword).get() << "protected";
    Printer << ":";
  } else if (Access == PDB_MemberAccess::Public) {
    Printer.NewLine();
    WithColor(Printer, PDB_ColorItem::Keyword).get() << "public";
    Printer << ":";
  }
  Printer.Indent();
  for (auto iter = Group.Functions.begin(), end = Group.Functions.end();
       iter != end; ++iter) {
    ++Count;
    (*iter)->dump(*this);
  }
  for (auto iter = Group.Data.begin(), end = Group.Data.end(); iter != end;
       ++iter) {
    ++Count;
    (*iter)->dump(*this);
  }
  for (auto iter = Group.Unknown.begin(), end = Group.Unknown.end();
       iter != end; ++iter) {
    ++Count;
    (*iter)->dump(*this);
  }
  Printer.Unindent();
  return Count;
}
