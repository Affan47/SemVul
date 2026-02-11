WidenVecRes_EXTRACT_SUBVECTOR(SDNode *N) {
  EVT      VT = N->getValueType(0);
  EVT      WidenVT = TLI.getTypeToTransformTo(*DAG.getContext(), VT);
  unsigned WidenNumElts = WidenVT.getVectorNumElements();
  SDValue  InOp = N->getOperand(0);
  SDValue  Idx  = N->getOperand(1);
  SDLoc dl(N);

  if (getTypeAction(InOp.getValueType()) == TargetLowering::TypeWidenVector)
    InOp = GetWidenedVector(InOp);

  EVT InVT = InOp.getValueType();


  uint64_t IdxVal = cast<ConstantSDNode>(Idx)->getZExtValue();
  if (IdxVal == 0 && InVT == WidenVT)
    return InOp;


  unsigned InNumElts = InVT.getVectorNumElements();
  if (IdxVal % WidenNumElts == 0 && IdxVal + WidenNumElts < InNumElts)
    return DAG.getNode(ISD::EXTRACT_SUBVECTOR, dl, WidenVT, InOp, Idx);


  SmallVector<SDValue, 16> Ops(WidenNumElts);
  EVT EltVT = VT.getVectorElementType();
  unsigned NumElts = VT.getVectorNumElements();
  unsigned i;
  for (i=0; i < NumElts; ++i)
    Ops[i] =
        DAG.getNode(ISD::EXTRACT_VECTOR_ELT, dl, EltVT, InOp,
                    DAG.getConstant(IdxVal + i, dl,
                                    TLI.getVectorIdxTy(DAG.getDataLayout())));

  SDValue UndefVal = DAG.getUNDEF(EltVT);
  for (; i < WidenNumElts; ++i)
    Ops[i] = UndefVal;
  return DAG.getNode(ISD::BUILD_VECTOR, dl, WidenVT, Ops);
}
