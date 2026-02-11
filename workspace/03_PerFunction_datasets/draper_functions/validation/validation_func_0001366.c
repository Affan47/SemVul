getReturnAddressFrameIndex(SelectionDAG &DAG) const {
  MachineFunction &MF = DAG.getMachineFunction();
  MSP430MachineFunctionInfo *FuncInfo = MF.getInfo<MSP430MachineFunctionInfo>();
  int ReturnAddrIndex = FuncInfo->getRAIndex();
  auto PtrVT = getPointerTy(MF.getDataLayout());

  if (ReturnAddrIndex == 0) {

    uint64_t SlotSize = MF.getDataLayout().getPointerSize();
    ReturnAddrIndex = MF.getFrameInfo()->CreateFixedObject(SlotSize, -SlotSize,
                                                           true);
    FuncInfo->setRAIndex(ReturnAddrIndex);
  }

  return DAG.getFrameIndex(ReturnAddrIndex, PtrVT);
}
