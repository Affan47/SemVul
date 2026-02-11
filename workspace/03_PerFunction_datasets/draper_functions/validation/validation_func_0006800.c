inet6_option_append (cmsg, typep, multx, plusy)
     struct cmsghdr *cmsg;
     const uint8_t *typep;
     int multx;
     int plusy;
{


  int len = typep[0] == IP6OPT_PAD1 ? 1 : typep[1] + 2;


  uint8_t *ptr = option_alloc (cmsg, len, multx, plusy);
  if (ptr == NULL)

    return -1;


  memcpy (ptr, typep, len);

  return 0;
}
