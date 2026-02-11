isGAPlusOffset(SDNode *N, const GlobalValue* &GA,
                                    int64_t &Offset) const {
  if (isa<GlobalAddressSDNode>(N)) {
    GlobalAddressSDNode *GASD = cast<GlobalAddressSDNode>(N);
    GA = GASD->getGlobal();
    Offset += GASD->getOffset();
    return true;
  }

  if (N->getOpcode() == ISD::ADD) {
    SDValue N1 = N->getOperand(0);
    SDValue N2 = N->getOperand(1);
    if (isGAPlusOffset(N1.getNode(), GA, Offset)) {
      ConstantSDNode *V = dyn_cast<ConstantSDNode>(N2);
      if (V) {
        Offset += V->getSExtValue();
        return true;
      }
    } else if (isGAPlusOffset(N2.getNode(), GA, Offset)) {
      ConstantSDNode *V = dyn_cast<ConstantSDNode>(N1);
      if (V) {
        Offset += V->getSExtValue();
        return true;
      }
    }
  }
  return false;
}
