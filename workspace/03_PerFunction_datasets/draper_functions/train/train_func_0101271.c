initFromAPInt(const APInt& api, bool isIEEE)
{
  if (api.getBitWidth() == 16)
    return initFromHalfAPInt(api);
  else if (api.getBitWidth() == 32)
    return initFromFloatAPInt(api);
  else if (api.getBitWidth()==64)
    return initFromDoubleAPInt(api);
  else if (api.getBitWidth()==80)
    return initFromF80LongDoubleAPInt(api);
  else if (api.getBitWidth()==128)
    return (isIEEE ?
            initFromQuadrupleAPInt(api) : initFromPPCDoubleDoubleAPInt(api));
  else
    llvm_unreachable(0);
}
