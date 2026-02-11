convertValue(IntInit *II) {
  int64_t Value = II->getValue();

  if (!canFitInBitfield(Value, Size))
    return 0;

  SmallVector<Init *, 16> NewBits(Size);

  for (unsigned i = 0; i != Size; ++i)
    NewBits[i] = BitInit::get(Value & (1LL << i));

  return BitsInit::get(NewBits);
}
