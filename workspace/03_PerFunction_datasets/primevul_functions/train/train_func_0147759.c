const KaxReferenceBlock & KaxBlockGroup::Reference(unsigned int Index) const
{
  KaxReferenceBlock * MyBlockAdds = static_cast<KaxReferenceBlock *>(FindFirstElt(EBML_INFO(KaxReferenceBlock)));
  assert(MyBlockAdds != NULL);

  while (Index != 0) {
    MyBlockAdds = static_cast<KaxReferenceBlock *>(FindNextElt(*MyBlockAdds));
    assert(MyBlockAdds != NULL);
    Index--;
  }
  return *MyBlockAdds;
}
