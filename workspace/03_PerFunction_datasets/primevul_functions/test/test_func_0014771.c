static inline Quantum GetChannelValue(unsigned int word,unsigned char channel,
  TIM2ColorEncoding ce)
{
  switch(ce)
  {
    case RGBA16:

      return ScaleCharToQuantum((word>>channel*5 & ~(~0x0U<<5))<<3);
    case RGB24:
    case RGBA32:
      return ScaleCharToQuantum(word>>channel*8 & ~(~0x0U<<8));
    default:
      return QuantumRange;
  }
}
