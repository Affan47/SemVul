_is_reserved_ipv6_iid(const guint8 *iid)
{


    if (memcmp(iid, &nm_ip_addr_zero.addr6.s6_addr[8], 8) == 0)
        return TRUE;


    if (memcmp(iid, (const guint8[]){0x02, 0x00, 0x5E, 0xFF, 0xFE}, 5) == 0)
        return TRUE;


    if (memcmp(iid, (const guint8[]){0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 7) == 0) {
        if (iid[7] & 0x80)
            return TRUE;
    }

    return FALSE;
}
