ExpandDivRemLibCall(SDNode *Node,
                                          SmallVectorImpl<SDValue> &Results) {
  unsigned Opcode = Node->getOpcode();
  bool isSigned = Opcode == ISD::SDIVREM;

  RTLIB::Libcall LC;
  switch (Node->getSimpleValueType(0).SimpleTy) {
  default: llvm_unreachable("Unexpected request for libcall!");
  case MVT::i8:   LC= isSigned ? RTLIB::SDIVREM_I8  : RTLIB::UDIVREM_I8;  break;
  case MVT::i16:  LC= isSigned ? RTLIB::SDIVREM_I16 : RTLIB::UDIVREM_I16; break;
  case MVT::i32:  LC= isSigned ? RTLIB::SDIVREM_I32 : RTLIB::UDIVREM_I32; break;
  case MVT::i64:  LC= isSigned ? RTLIB::SDIVREM_I64 : RTLIB::UDIVREM_I64; break;
  case MVT::i128: LC= isSigned ? RTLIB::SDIVREM_I128:RTLIB::UDIVREM_I128; break;
  }


  SDValue InChain = DAG.getEntryNode();

  EVT RetVT = Node->getValueType(0);
  Type *RetTy = RetVT.getTypeForEVT(*DAG.getContext());

  TargetLowering::ArgListTy Args;
  TargetLowering::ArgListEntry Entry;
  for (const SDValue &Op : Node->op_values()) {
    EVT ArgVT = Op.getValueType();
    Type *ArgTy = ArgVT.getTypeForEVT(*DAG.getContext());
    Entry.Node = Op;
    Entry.Ty = ArgTy;
    Entry.isSExt = isSigned;
    Entry.isZExt = !isSigned;
    Args.push_back(Entry);
  }


  SDValue FIPtr = DAG.CreateStackTemporary(RetVT);
  Entry.Node = FIPtr;
  Entry.Ty = RetTy->getPointerTo();
  Entry.isSExt = isSigned;
  Entry.isZExt = !isSigned;
  Args.push_back(Entry);

  SDValue Callee = DAG.getExternalSymbol(TLI.getLibcallName(LC),
                                         TLI.getPointerTy(DAG.getDataLayout()));

  SDLoc dl(Node);
  TargetLowering::CallLoweringInfo CLI(DAG);
  CLI.setDebugLoc(dl).setChain(InChain)
    .setCallee(TLI.getLibcallCallingConv(LC), RetTy, Callee, std::move(Args), 0)
    .setSExtResult(isSigned).setZExtResult(!isSigned);

  std::pair<SDValue, SDValue> CallInfo = TLI.LowerCallTo(CLI);


  SDValue Rem = DAG.getLoad(RetVT, dl, CallInfo.second, FIPtr,
                            MachinePointerInfo(), false, false, false, 0);
  Results.push_back(CallInfo.first);
  Results.push_back(Rem);
}
