getBlockFreq(const BlockNode &Node) const {
  if (!Node.isValid())
    return 0;
  return Freqs[Node.Index].Integer;
}
