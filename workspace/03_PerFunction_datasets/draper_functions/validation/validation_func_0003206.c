nodeList() const
{
  NodePtr tem(new DocumentTypeNode(grove(), grove()->governingDtd()));
  return new SiblingNodeList(tem);
}
