qemuProcessGenID(virDomainObjPtr vm,
                 unsigned int flags)
{
    if (!vm->def->genidRequested)
        return 0;


    if (flags & VIR_QEMU_PROCESS_START_GEN_VMID) {
        if (virUUIDGenerate(vm->def->genid) < 0) {
            virReportError(VIR_ERR_INTERNAL_ERROR, "%s",
                           _("failed to regenerate genid"));
            return -1;
        }
    }

    return 0;
}
