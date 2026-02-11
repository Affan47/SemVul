ColorComponentRealToByte(
  float color)
{
  int val=static_cast<int>(color*255.0);
  if(val>255)
    {
    val=255;
    }
  else
    {
    if(val<0)
      {
      val=0;
      }
    }
  return static_cast<unsigned char>(val);
}
