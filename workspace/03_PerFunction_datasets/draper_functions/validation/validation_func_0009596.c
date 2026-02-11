_gnutls_mem_cpy (char *dest, size_t dest_tot_size, const char *src,
                 size_t src_size)
{

  if (dest_tot_size >= src_size)
    {
      memcpy (dest, src, src_size);
    }
  else
    {
      if (dest_tot_size > 0)
        {
          memcpy (dest, src, dest_tot_size);
        }
    }
}
