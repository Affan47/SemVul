int CodedSizeLengthSigned(int64 Length, unsigned int SizeLength)
{
  unsigned int CodedSize;


  if (Length > -64 && Length < 64)
    CodedSize = 1;
  else if (Length > -8192 && Length < 8192)
    CodedSize = 2;
  else if (Length > -1048576L && Length < 1048576L)
    CodedSize = 3;
  else if (Length > -134217728L && Length < 134217728L)
    CodedSize = 4;
  else CodedSize = 5;

  if (SizeLength > 0 && CodedSize < SizeLength) {

    CodedSize = SizeLength;
  }

  return CodedSize;
}
