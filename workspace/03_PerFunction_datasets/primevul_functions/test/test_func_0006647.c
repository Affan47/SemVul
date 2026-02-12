static void bitmapFromData(const unsigned short data[], int nData,
                           unsigned char bitmap[BITMAP_SIZE],
                           unsigned short &minNonZero,
                           unsigned short &maxNonZero) {
  for (int i = 0; i < BITMAP_SIZE; ++i) bitmap[i] = 0;

  for (int i = 0; i < nData; ++i) bitmap[data[i] >> 3] |= (1 << (data[i] & 7));

  bitmap[0] &= ~1;


  minNonZero = BITMAP_SIZE - 1;
  maxNonZero = 0;

  for (int i = 0; i < BITMAP_SIZE; ++i) {
    if (bitmap[i]) {
      if (minNonZero > i) minNonZero = i;
      if (maxNonZero < i) maxNonZero = i;
    }
  }
}
