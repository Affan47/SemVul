static void applyLut(const unsigned short lut[USHORT_RANGE],
                     unsigned short data[], int nData) {
  for (int i = 0; i < nData; ++i) data[i] = lut[data[i]];
}
