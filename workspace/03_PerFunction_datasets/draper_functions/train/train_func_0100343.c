currentNodePageNumber(const NodePtr &node)
{
  inlinePrepare();
  syncCharFormat();
  GroveString id;
  unsigned long n;
  if (node->getId(id) == accessOK) {
    os() << "{\\field\\flddirty{\\*\\fldinst PAGEREF ";
    outputBookmarkName(node->groveIndex(), id.data(), id.size());
    os() << "}{\\fldrslt 000}}";
  }
  else if (node->elementIndex(n) == accessOK) {
    os() << "{\\field\\flddirty{\\*\\fldinst PAGEREF ";
    unsigned long groveIndex = node->groveIndex();
    outputBookmarkName(groveIndex, n);
    elementsRefed_.add(groveIndex, n);
    os() << "}{\\fldrslt 000}}";
  }
}
