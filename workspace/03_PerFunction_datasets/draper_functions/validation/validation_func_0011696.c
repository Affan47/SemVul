offsetsDoNotOverlap(int WidthA, int OffsetA,
                                int WidthB, int OffsetB) {
  int LowOffset = OffsetA < OffsetB ? OffsetA : OffsetB;
  int HighOffset = OffsetA < OffsetB ? OffsetB : OffsetA;
  int LowWidth = (LowOffset == OffsetA) ? WidthA : WidthB;
  return LowOffset + LowWidth <= HighOffset;
}
