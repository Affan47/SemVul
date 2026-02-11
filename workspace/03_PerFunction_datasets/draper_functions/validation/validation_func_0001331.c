getAddressOperandsRI(const SystemZRRIAddressMode &AM,
                                               SDValue &Base, SDValue &Disp) {
  if (AM.BaseType == SystemZRRIAddressMode::RegBase)
    Base = AM.Base.Reg;
  else
    Base = CurDAG->getTargetFrameIndex(AM.Base.FrameIndex, TLI.getPointerTy());
  Disp = CurDAG->getTargetConstant(AM.Disp, MVT::i64);
}
