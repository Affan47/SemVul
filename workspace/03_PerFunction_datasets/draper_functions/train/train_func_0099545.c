replace(int iSys, int iPosOld, int iPosNew) {

  if (systems[iSys].iInA == iPosOld) {
    systems[iSys].iInA = iPosNew;
    return;
  }
  if (systems[iSys].iInB == iPosOld) {
    systems[iSys].iInB = iPosNew;
    return;
  }
  for (int i = 0; i < sizeOut(iSys); ++i)
  if (systems[iSys].iOut[i] == iPosOld) {
    systems[iSys].iOut[i] = iPosNew;
    return;
  }

}
