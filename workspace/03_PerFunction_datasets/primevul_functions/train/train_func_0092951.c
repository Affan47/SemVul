int CodedSizeLength(uint64 Length, unsigned int SizeLength, bool bSizeFinite)
{
  unsigned int CodedSize;
  if (bSizeFinite) {


    if (Length < 127)
      CodedSize = 1;
    else if (Length < 16383)
      CodedSize = 2;
    else if (Length < 2097151L)
      CodedSize = 3;
    else if (Length < 268435455L)
      CodedSize = 4;
    else CodedSize = 5;
  } else {
    if (Length <= 127)
      CodedSize = 1;
    else if (Length <= 16383)
      CodedSize = 2;
    else if (Length <= 2097151L)
      CodedSize = 3;
    else if (Length <= 268435455L)
      CodedSize = 4;
    else CodedSize = 5;
  }

  if (SizeLength > 0 && CodedSize < SizeLength) {

    CodedSize = SizeLength;
  }

  return CodedSize;
}
