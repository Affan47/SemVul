static inline Quantum GetAlpha(unsigned int word,TIM2ColorEncoding ce)
{
  switch(ce)
  {
    case RGBA16:
      return ScaleCharToQuantum((word>>3*5&0x1F)==0?0:0xFF);
    case RGBA32:

      return ScaleCharToQuantum(MagickMin((word>>3*8&0xFF)<<1,0xFF));
    default:
      return 0xFF;
  }
}
