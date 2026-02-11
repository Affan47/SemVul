lowerLoadWordFromAlignedBasePlusOffset(SDLoc DL, SDValue Chain, SDValue Base,
                                       int64_t Offset, SelectionDAG &DAG) const
{
  auto PtrVT = getPointerTy(DAG.getDataLayout());
  if ((Offset & 0x3) == 0) {
    return DAG.getLoad(PtrVT, DL, Chain, Base, MachinePointerInfo(), false,
                       false, false, 0);
  }

  int32_t HighOffset = RoundUpToAlignment(Offset, 4);
  int32_t LowOffset = HighOffset - 4;
  SDValue LowAddr, HighAddr;
  if (GlobalAddressSDNode *GASD =
        dyn_cast<GlobalAddressSDNode>(Base.getNode())) {
    LowAddr = DAG.getGlobalAddress(GASD->getGlobal(), DL, Base.getValueType(),
                                   LowOffset);
    HighAddr = DAG.getGlobalAddress(GASD->getGlobal(), DL, Base.getValueType(),
                                    HighOffset);
  } else {
    LowAddr = DAG.getNode(ISD::ADD, DL, MVT::i32, Base,
                          DAG.getConstant(LowOffset, DL, MVT::i32));
    HighAddr = DAG.getNode(ISD::ADD, DL, MVT::i32, Base,
                           DAG.getConstant(HighOffset, DL, MVT::i32));
  }
  SDValue LowShift = DAG.getConstant((Offset - LowOffset) * 8, DL, MVT::i32);
  SDValue HighShift = DAG.getConstant((HighOffset - Offset) * 8, DL, MVT::i32);

  SDValue Low = DAG.getLoad(PtrVT, DL, Chain, LowAddr, MachinePointerInfo(),
                            false, false, false, 0);
  SDValue High = DAG.getLoad(PtrVT, DL, Chain, HighAddr, MachinePointerInfo(),
                             false, false, false, 0);
  SDValue LowShifted = DAG.getNode(ISD::SRL, DL, MVT::i32, Low, LowShift);
  SDValue HighShifted = DAG.getNode(ISD::SHL, DL, MVT::i32, High, HighShift);
  SDValue Result = DAG.getNode(ISD::OR, DL, MVT::i32, LowShifted, HighShifted);
  Chain = DAG.getNode(ISD::TokenFactor, DL, MVT::Other, Low.getValue(1),
                      High.getValue(1));
  SDValue Ops[] = { Result, Chain };
  return DAG.getMergeValues(Ops, DL);
}
