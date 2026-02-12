static inline unsigned int ByteMultiply(const unsigned char alpha,
  const unsigned char beta)
{


  if ((alpha == 0) || (beta == 0))
    return(0);
  return((unsigned int) InverseLog[(Log[alpha]+Log[beta]) % 0xff]);
}
