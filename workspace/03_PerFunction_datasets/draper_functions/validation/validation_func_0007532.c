SoftenFloatRes_LOAD(SDNode *N) {
  LoadSDNode *L = cast<LoadSDNode>(N);
  EVT VT = N->getValueType(0);
  EVT NVT = TLI.getTypeToTransformTo(*DAG.getContext(), VT);
  SDLoc dl(N);

  SDValue NewL;
  if (L->getExtensionType() == ISD::NON_EXTLOAD) {
    NewL = DAG.getLoad(L->getAddressingMode(), L->getExtensionType(),
                       NVT, dl, L->getChain(), L->getBasePtr(), L->getOffset(),
                       L->getPointerInfo(), NVT, L->isVolatile(),
                       L->isNonTemporal(), false, L->getAlignment(),
                       L->getAAInfo());


    ReplaceValueWith(SDValue(N, 1), NewL.getValue(1));
    return NewL;
  }


  NewL = DAG.getLoad(L->getAddressingMode(), ISD::NON_EXTLOAD,
                     L->getMemoryVT(), dl, L->getChain(),
                     L->getBasePtr(), L->getOffset(), L->getPointerInfo(),
                     L->getMemoryVT(), L->isVolatile(),
                     L->isNonTemporal(), false, L->getAlignment(),
                     L->getAAInfo());


  ReplaceValueWith(SDValue(N, 1), NewL.getValue(1));
  return BitConvertToInteger(DAG.getNode(ISD::FP_EXTEND, dl, VT, NewL));
}
