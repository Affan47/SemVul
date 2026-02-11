LowerINIT_TRAMPOLINE(SDValue Op, SelectionDAG &DAG) const {
  SDValue Chain = Op.getOperand(0);
  SDValue Trmp = Op.getOperand(1);
  SDValue FPtr = Op.getOperand(2);
  SDValue Nest = Op.getOperand(3);

  const Value *TrmpAddr = cast<SrcValueSDNode>(Op.getOperand(4))->getValue();


  SDValue OutChains[5];

  SDValue Addr = Trmp;

  SDLoc dl(Op);
  OutChains[0] = DAG.getStore(Chain, dl,
                              DAG.getConstant(0x0a3cd805, dl, MVT::i32), Addr,
                              MachinePointerInfo(TrmpAddr), false, false, 0);

  Addr = DAG.getNode(ISD::ADD, dl, MVT::i32, Trmp,
                     DAG.getConstant(4, dl, MVT::i32));
  OutChains[1] = DAG.getStore(Chain, dl,
                              DAG.getConstant(0xd80456c0, dl, MVT::i32), Addr,
                              MachinePointerInfo(TrmpAddr, 4), false, false, 0);

  Addr = DAG.getNode(ISD::ADD, dl, MVT::i32, Trmp,
                     DAG.getConstant(8, dl, MVT::i32));
  OutChains[2] = DAG.getStore(Chain, dl,
                              DAG.getConstant(0x27fb0a3c, dl, MVT::i32), Addr,
                              MachinePointerInfo(TrmpAddr, 8), false, false, 0);

  Addr = DAG.getNode(ISD::ADD, dl, MVT::i32, Trmp,
                     DAG.getConstant(12, dl, MVT::i32));
  OutChains[3] = DAG.getStore(Chain, dl, Nest, Addr,
                              MachinePointerInfo(TrmpAddr, 12), false, false,
                              0);

  Addr = DAG.getNode(ISD::ADD, dl, MVT::i32, Trmp,
                     DAG.getConstant(16, dl, MVT::i32));
  OutChains[4] = DAG.getStore(Chain, dl, FPtr, Addr,
                              MachinePointerInfo(TrmpAddr, 16), false, false,
                              0);

  return DAG.getNode(ISD::TokenFactor, dl, MVT::Other, OutChains);
}
