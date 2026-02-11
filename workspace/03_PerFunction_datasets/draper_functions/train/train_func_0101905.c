SelectAdd(SDNode *N) {
  SDLoc dl(N);
  if (N->getValueType(0) != MVT::i32) {
    return SelectCode(N);
  }

  SDNode* Src1 = N->getOperand(0).getNode();
  if (Src1->getOpcode() != ISD::SRA || !Src1->hasOneUse()
      || Src1->getValueType(0) != MVT::i32) {
    return SelectCode(N);
  }


  SDNode* Result = CurDAG->getMachineNode(Hexagon::S2_asr_r_r_acc, dl, MVT::i32,
                                          N->getOperand(1),
                                          Src1->getOperand(0),
                                          Src1->getOperand(1));
  ReplaceUses(N, Result);

  return Result;
}
