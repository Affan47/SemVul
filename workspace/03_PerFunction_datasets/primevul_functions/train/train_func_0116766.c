qemuProcessRecoverMigrationOut(virQEMUDriverPtr driver,
                               virDomainObjPtr vm,
                               const qemuDomainJobObj *job,
                               virDomainState state,
                               int reason,
                               unsigned int *stopFlags)
{
    qemuDomainJobPrivatePtr jobPriv = job->privateData;
    bool postcopy = state == VIR_DOMAIN_PAUSED &&
                    (reason == VIR_DOMAIN_PAUSED_POSTCOPY ||
                     reason == VIR_DOMAIN_PAUSED_POSTCOPY_FAILED);
    bool resume = false;

    switch ((qemuMigrationJobPhase) job->phase) {
    case QEMU_MIGRATION_PHASE_NONE:
    case QEMU_MIGRATION_PHASE_PREPARE:
    case QEMU_MIGRATION_PHASE_FINISH2:
    case QEMU_MIGRATION_PHASE_FINISH3:
    case QEMU_MIGRATION_PHASE_LAST:

        break;

    case QEMU_MIGRATION_PHASE_BEGIN3:


        break;

    case QEMU_MIGRATION_PHASE_PERFORM2:
    case QEMU_MIGRATION_PHASE_PERFORM3:


        if (postcopy) {
            qemuMigrationAnyPostcopyFailed(driver, vm);
        } else {
            VIR_DEBUG("Cancelling unfinished migration of domain %s",
                      vm->def->name);
            if (qemuMigrationSrcCancel(driver, vm) < 0) {
                VIR_WARN("Could not cancel ongoing migration of domain %s",
                         vm->def->name);
            }
            resume = true;
        }
        break;

    case QEMU_MIGRATION_PHASE_PERFORM3_DONE:


        if (postcopy)
            qemuMigrationAnyPostcopyFailed(driver, vm);
        break;

    case QEMU_MIGRATION_PHASE_CONFIRM3_CANCELLED:


        if (postcopy) {
            qemuMigrationAnyPostcopyFailed(driver, vm);
        } else {
            VIR_DEBUG("Resuming domain %s after failed migration",
                      vm->def->name);
            resume = true;
        }
        break;

    case QEMU_MIGRATION_PHASE_CONFIRM3:

        *stopFlags |= VIR_QEMU_PROCESS_STOP_MIGRATED;
        return -1;
    }

    if (resume) {


        if (state == VIR_DOMAIN_PAUSED &&
            (reason == VIR_DOMAIN_PAUSED_MIGRATION ||
             reason == VIR_DOMAIN_PAUSED_UNKNOWN)) {
            if (qemuProcessStartCPUs(driver, vm,
                                     VIR_DOMAIN_RUNNING_MIGRATION_CANCELED,
                                     QEMU_ASYNC_JOB_NONE) < 0) {
                VIR_WARN("Could not resume domain %s", vm->def->name);
            }
        }
    }

    qemuMigrationParamsReset(driver, vm, QEMU_ASYNC_JOB_NONE,
                             jobPriv->migParams, job->apiFlags);
    return 0;
}
