_gcry_private_is_secure (const void *p)
{
  return pool_okay && ptr_into_pool_p (p);
}
