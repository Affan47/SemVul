secondSynchByte(char byte)
{
  if(uchar(byte) == 0xff)
    return false;

  std::bitset<8> b(byte);


  return b.test(7) && b.test(6) && b.test(5);
}
