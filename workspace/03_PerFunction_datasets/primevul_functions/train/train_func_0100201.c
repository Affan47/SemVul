libxlNetworkPrepareDevices(virDomainDef *def)
{
    size_t i;
    g_autoptr(virConnect) conn = NULL;

    for (i = 0; i < def->nnets; i++) {
        virDomainNetDef *net = def->nets[i];
        virDomainNetType actualType;


        if (net->type == VIR_DOMAIN_NET_TYPE_NETWORK) {
            if (!conn && !(conn = virGetConnectNetwork()))
                return -1;
            if (virDomainNetAllocateActualDevice(conn, def, net) < 0)
                return -1;
        }


        if (virDomainActualNetDefValidate(net) < 0)
            return -1;

        actualType = virDomainNetGetActualType(net);
        if (actualType == VIR_DOMAIN_NET_TYPE_HOSTDEV &&
            net->type == VIR_DOMAIN_NET_TYPE_NETWORK) {


            virDomainHostdevDef *hostdev = virDomainNetGetActualHostdev(net);
            virDomainHostdevSubsysPCI *pcisrc = &hostdev->source.subsys.u.pci;

            if (hostdev->mode == VIR_DOMAIN_HOSTDEV_MODE_SUBSYS &&
                hostdev->source.subsys.type == VIR_DOMAIN_HOSTDEV_SUBSYS_TYPE_PCI)
                pcisrc->backend = VIR_DOMAIN_HOSTDEV_PCI_BACKEND_XEN;

            if (virDomainHostdevInsert(def, hostdev) < 0)
                return -1;
        }
    }

    return 0;
}
