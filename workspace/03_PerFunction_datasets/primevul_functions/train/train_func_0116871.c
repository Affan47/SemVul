qemuProcessUpdateSEVInfo(virDomainObjPtr vm)
{
    qemuDomainObjPrivatePtr priv = vm->privateData;
    virQEMUCapsPtr qemuCaps = priv->qemuCaps;
    virDomainSEVDefPtr sev = vm->def->sev;
    virSEVCapabilityPtr sevCaps = NULL;


    sevCaps = virQEMUCapsGetSEVCapabilities(qemuCaps);
    if (!sev->haveCbitpos) {
        sev->cbitpos = sevCaps->cbitpos;
        sev->haveCbitpos = true;
    }

    if (!sev->haveReducedPhysBits) {
        sev->reduced_phys_bits = sevCaps->reduced_phys_bits;
        sev->haveReducedPhysBits = true;
    }

    return 0;
}
