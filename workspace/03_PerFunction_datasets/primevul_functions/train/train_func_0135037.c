nm_utils_arp_type_detect_from_hwaddrlen(gsize hwaddr_len)
{
    switch (hwaddr_len) {
    case ETH_ALEN:
        return ARPHRD_ETHER;
    case INFINIBAND_ALEN:
        return ARPHRD_INFINIBAND;
    default:


        return -EINVAL;
    }
}
