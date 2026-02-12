clip_dns_ttl(uint32_t ttl)
{


  if (ttl < MIN_DNS_TTL)
    return MIN_DNS_TTL;
  else
    return MAX_DNS_TTL;
}
