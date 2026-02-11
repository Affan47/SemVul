SelectT2AddrModeImm8Offset(SDNode *Op, SDValue N,
                                                 SDValue &OffImm){
  unsigned Opcode = Op->getOpcode();
  ISD::MemIndexedMode AM = (Opcode == ISD::LOAD)
    ? cast<LoadSDNode>(Op)->getAddressingMode()
    : cast<StoreSDNode>(Op)->getAddressingMode();
  int RHSC;
  if (isScaledConstantInRange(N, 1, 0, 0x100, RHSC)) {
    OffImm = ((AM == ISD::PRE_INC) || (AM == ISD::POST_INC))
      ? CurDAG->getTargetConstant(RHSC, SDLoc(N), MVT::i32)
      : CurDAG->getTargetConstant(-RHSC, SDLoc(N), MVT::i32);
    return true;
  }

  return false;
}
