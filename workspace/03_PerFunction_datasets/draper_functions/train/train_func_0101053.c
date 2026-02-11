Decode(std::istream &is, std::ostream &os)
{
  unsigned char packedbytes;
  unsigned char unpackedbytes[8];
  while( is.read((char*)&packedbytes,1) )
    {
    unsigned char mask = 1;
    for (unsigned int i = 0; i < 8; ++i)
      {
      if ( (packedbytes & mask) == 0)
        {
        unpackedbytes[i] = 0;
        }
      else
        {
        unpackedbytes[i] = 1;
        }
      mask <<= 1;
      }
    os.write(reinterpret_cast<char*>(unpackedbytes), 8);
    }
}
