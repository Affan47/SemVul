qemuProcessPrepareDomainNUMAPlacement(virDomainObjPtr vm)
{
    qemuDomainObjPrivatePtr priv = vm->privateData;
    g_autofree char *nodeset = NULL;
    g_autoptr(virBitmap) numadNodeset = NULL;
    g_autoptr(virBitmap) hostMemoryNodeset = NULL;
    g_autoptr(virCapsHostNUMA) caps = NULL;


    if (!virDomainDefNeedsPlacementAdvice(vm->def))
        return 0;

    nodeset = virNumaGetAutoPlacementAdvice(virDomainDefGetVcpus(vm->def),
                                            virDomainDefGetMemoryTotal(vm->def));

    if (!nodeset)
        return -1;

    if (!(hostMemoryNodeset = virNumaGetHostMemoryNodeset()))
        return -1;

    VIR_DEBUG("Nodeset returned from numad: %s", nodeset);

    if (virBitmapParse(nodeset, &numadNodeset, VIR_DOMAIN_CPUMASK_LEN) < 0)
        return -1;

    if (!(caps = virCapabilitiesHostNUMANewHost()))
        return -1;


    if (!(priv->autoCpuset = virCapabilitiesHostNUMAGetCpus(caps, numadNodeset)))
        return -1;

    virBitmapIntersect(numadNodeset, hostMemoryNodeset);

    priv->autoNodeset = g_steal_pointer(&numadNodeset);

    return 0;
}
