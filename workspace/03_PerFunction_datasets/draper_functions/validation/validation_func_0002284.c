GNUNET_CRYPTO_hash_matching_bits (const GNUNET_HashCode * first,
                                  const GNUNET_HashCode * second)
{
  unsigned int i;

  for (i = 0; i < sizeof (GNUNET_HashCode) * 8; i++)
    if (GNUNET_CRYPTO_hash_get_bit (first, i) !=
        GNUNET_CRYPTO_hash_get_bit (second, i))
      return i;
  return sizeof (GNUNET_HashCode) * 8;
}
