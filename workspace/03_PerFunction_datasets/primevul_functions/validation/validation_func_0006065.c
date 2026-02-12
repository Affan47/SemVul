multi_select_virtual_addr(struct multi_context *m, struct multi_instance *mi)
{
    struct gc_arena gc = gc_new();


    if (mi->context.options.push_ifconfig_defined)
    {


        if (mi->vaddr_handle >= 0)
        {
            ifconfig_pool_release(m->ifconfig_pool, mi->vaddr_handle, true);
            mi->vaddr_handle = -1;
        }

        mi->context.c2.push_ifconfig_defined = true;
        mi->context.c2.push_ifconfig_local = mi->context.options.push_ifconfig_local;
        mi->context.c2.push_ifconfig_remote_netmask = mi->context.options.push_ifconfig_remote_netmask;
        mi->context.c2.push_ifconfig_local_alias = mi->context.options.push_ifconfig_local_alias;


        if (mi->context.options.ifconfig_ipv6_pool_defined
            && !mi->context.options.push_ifconfig_ipv6_defined)
        {
            msg( M_INFO, "MULTI_sva: WARNING: if --ifconfig-push is used for IPv4, automatic IPv6 assignment from --ifconfig-ipv6-pool does not work.  Use --ifconfig-ipv6-push for IPv6 then." );
        }
    }
    else if (m->ifconfig_pool && mi->vaddr_handle < 0)
    {
        in_addr_t local = 0, remote = 0;
        struct in6_addr remote_ipv6;
        const char *cn = NULL;

        if (!mi->context.options.duplicate_cn)
        {
            cn = tls_common_name(mi->context.c2.tls_multi, true);
        }

        CLEAR(remote_ipv6);
        mi->vaddr_handle = ifconfig_pool_acquire(m->ifconfig_pool, &local, &remote, &remote_ipv6, cn);
        if (mi->vaddr_handle >= 0)
        {
            const int tunnel_type = TUNNEL_TYPE(mi->context.c1.tuntap);
            const int tunnel_topology = TUNNEL_TOPOLOGY(mi->context.c1.tuntap);

            msg( M_INFO, "MULTI_sva: pool returned IPv4=%s, IPv6=%s",
                 print_in_addr_t( remote, 0, &gc ),
                 (mi->context.options.ifconfig_ipv6_pool_defined
                  ? print_in6_addr( remote_ipv6, 0, &gc )
                  : "(Not enabled)") );


            mi->context.c2.push_ifconfig_local = remote;
            if (tunnel_type == DEV_TYPE_TAP || (tunnel_type == DEV_TYPE_TUN && tunnel_topology == TOP_SUBNET))
            {
                mi->context.c2.push_ifconfig_remote_netmask = mi->context.options.ifconfig_pool_netmask;
                if (!mi->context.c2.push_ifconfig_remote_netmask)
                {
                    mi->context.c2.push_ifconfig_remote_netmask = mi->context.c1.tuntap->remote_netmask;
                }
            }
            else if (tunnel_type == DEV_TYPE_TUN)
            {
                if (tunnel_topology == TOP_P2P)
                {
                    mi->context.c2.push_ifconfig_remote_netmask = mi->context.c1.tuntap->local;
                }
                else if (tunnel_topology == TOP_NET30)
                {
                    mi->context.c2.push_ifconfig_remote_netmask = local;
                }
            }

            if (mi->context.c2.push_ifconfig_remote_netmask)
            {
                mi->context.c2.push_ifconfig_defined = true;
            }
            else
            {
                msg(D_MULTI_ERRORS, "MULTI: no --ifconfig-pool netmask parameter is available to push to %s",
                    multi_instance_string(mi, false, &gc));
            }

            if (mi->context.options.ifconfig_ipv6_pool_defined)
            {
                mi->context.c2.push_ifconfig_ipv6_local = remote_ipv6;
                mi->context.c2.push_ifconfig_ipv6_remote =
                    mi->context.c1.tuntap->local_ipv6;
                mi->context.c2.push_ifconfig_ipv6_netbits =
                    mi->context.options.ifconfig_ipv6_netbits;
                mi->context.c2.push_ifconfig_ipv6_defined = true;
            }
        }
        else
        {
            msg(D_MULTI_ERRORS, "MULTI: no free --ifconfig-pool addresses are available");
        }
    }


    if (mi->context.options.push_ifconfig_ipv6_defined)
    {
        mi->context.c2.push_ifconfig_ipv6_local =
            mi->context.options.push_ifconfig_ipv6_local;
        mi->context.c2.push_ifconfig_ipv6_remote =
            mi->context.options.push_ifconfig_ipv6_remote;
        mi->context.c2.push_ifconfig_ipv6_netbits =
            mi->context.options.push_ifconfig_ipv6_netbits;
        mi->context.c2.push_ifconfig_ipv6_defined = true;

        msg( M_INFO, "MULTI_sva: push_ifconfig_ipv6 %s/%d",
             print_in6_addr( mi->context.c2.push_ifconfig_ipv6_local, 0, &gc ),
             mi->context.c2.push_ifconfig_ipv6_netbits );
    }

    gc_free(&gc);
}
