type_to_str (const address_t * ad)
{
  if (!ad)
    return "<null addr>";
  switch (ad->type)
    {
    case AF_INET:
      return "IP";
    case AF_INET6:
      return "IPv6";
    default:
      return "<invalid address family>";
    }
}
