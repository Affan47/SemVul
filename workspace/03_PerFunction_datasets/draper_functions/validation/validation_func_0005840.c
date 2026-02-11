replaceInChain(SelectionDAG *CurDAG, SDValue Chain, SDValue Old, SDValue New)
{
  if (Chain == Old)
    return New;
  if (Chain->getOpcode() != ISD::TokenFactor)
    return SDValue();
  SmallVector<SDValue, 8> Ops;
  bool found = false;
  for (unsigned i = 0, e = Chain->getNumOperands(); i != e; ++i) {
    if (Chain->getOperand(i) == Old) {
      Ops.push_back(New);
      found = true;
    } else {
      Ops.push_back(Chain->getOperand(i));
    }
  }
  if (!found)
    return SDValue();
  return CurDAG->getNode(ISD::TokenFactor, SDLoc(Chain), MVT::Other, Ops);
}
