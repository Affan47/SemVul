getArgFlagsString() {
  std::string S = "< ";

  if (isZExt())
    S += "zext ";
  if (isSExt())
    S += "sext ";
  if (isInReg())
    S += "inreg ";
  if (isSRet())
    S += "sret ";
  if (isByVal())
    S += "byval ";
  if (isNest())
    S += "nest ";
  if (getByValAlign())
    S += "byval-align:" + utostr(getByValAlign()) + " ";
  if (getOrigAlign())
    S += "orig-align:" + utostr(getOrigAlign()) + " ";
  if (getByValSize())
    S += "byval-size:" + utostr(getByValSize()) + " ";
  return S + ">";
}
