static int64_t guest_ip_prefix(IP_ADAPTER_UNICAST_ADDRESS *ip_addr)
{


    return ip_addr->OnLinkPrefixLength;
}
