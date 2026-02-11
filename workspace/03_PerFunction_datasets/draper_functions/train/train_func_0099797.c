getMemset(SDValue Chain, DebugLoc dl, SDValue Dst,
                                SDValue Src, SDValue Size,
                                unsigned Align, bool isVol,
                                const Value *DstSV, uint64_t DstSVOff) {


  ConstantSDNode *ConstantSize = dyn_cast<ConstantSDNode>(Size);
  if (ConstantSize) {

    if (ConstantSize->isNullValue())
      return Chain;

    SDValue Result =
      getMemsetStores(*this, dl, Chain, Dst, Src, ConstantSize->getZExtValue(),
                      Align, isVol, DstSV, DstSVOff);

    if (Result.getNode())
      return Result;
  }


  SDValue Result =
    TSI.EmitTargetCodeForMemset(*this, dl, Chain, Dst, Src, Size, Align, isVol,
                                DstSV, DstSVOff);
  if (Result.getNode())
    return Result;


  const Type *IntPtrTy = TLI.getTargetData()->getIntPtrType(*getContext());
  TargetLowering::ArgListTy Args;
  TargetLowering::ArgListEntry Entry;
  Entry.Node = Dst; Entry.Ty = IntPtrTy;
  Args.push_back(Entry);

  if (Src.getValueType().bitsGT(MVT::i32))
    Src = getNode(ISD::TRUNCATE, dl, MVT::i32, Src);
  else
    Src = getNode(ISD::ZERO_EXTEND, dl, MVT::i32, Src);
  Entry.Node = Src;
  Entry.Ty = Type::getInt32Ty(*getContext());
  Entry.isSExt = true;
  Args.push_back(Entry);
  Entry.Node = Size;
  Entry.Ty = IntPtrTy;
  Entry.isSExt = false;
  Args.push_back(Entry);

  std::pair<SDValue,SDValue> CallResult =
    TLI.LowerCallTo(Chain, Type::getVoidTy(*getContext()),
                    false, false, false, false, 0,
                    TLI.getLibcallCallingConv(RTLIB::MEMSET), false,
                    false,
                    getExternalSymbol(TLI.getLibcallName(RTLIB::MEMSET),
                                      TLI.getPointerTy()),
                    Args, *this, dl);
  return CallResult.second;
}
