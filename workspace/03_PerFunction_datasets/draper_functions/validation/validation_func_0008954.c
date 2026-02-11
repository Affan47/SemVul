add_addr_print(const u_char *opt, u_int opt_len, u_char flags _U_)
{
        struct mp_add_addr *add_addr = (struct mp_add_addr *) opt;
        u_int ipver = MP_ADD_ADDR_IPVER(add_addr->sub_ipver);

        if (!((opt_len == 8 || opt_len == 10) && ipver == 4) &&
            !((opt_len == 20 || opt_len == 22) && ipver == 6))
                return 0;

        printf(" id %u", add_addr->addr_id);
        switch (ipver) {
        case 4:
                printf(" %s", ipaddr_string(add_addr->u.v4.addr));
                if (opt_len == 10)
                        printf(":%u", EXTRACT_16BITS(add_addr->u.v4.port));
                break;
        case 6:
#ifdef INET6
                printf(" %s", ip6addr_string(add_addr->u.v6.addr));
#endif
                if (opt_len == 22)
                        printf(":%u", EXTRACT_16BITS(add_addr->u.v6.port));
                break;
        default:
                return 0;
        }

        return 1;
}
