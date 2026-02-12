qemuProcessHandleBlockJob(qemuMonitorPtr mon G_GNUC_UNUSED,
                          virDomainObjPtr vm,
                          const char *diskAlias,
                          int type,
                          int status,
                          const char *error,
                          void *opaque)
{
    qemuDomainObjPrivatePtr priv;
    virQEMUDriverPtr driver = opaque;
    struct qemuProcessEvent *processEvent = NULL;
    virDomainDiskDefPtr disk;
    g_autoptr(qemuBlockJobData) job = NULL;
    char *data = NULL;

    virObjectLock(vm);

    priv = vm->privateData;


    if (virQEMUCapsGet(priv->qemuCaps, QEMU_CAPS_BLOCKDEV))
        goto cleanup;

    VIR_DEBUG("Block job for device %s (domain: %p,%s) type %d status %d",
              diskAlias, vm, vm->def->name, type, status);

    if (!(disk = qemuProcessFindDomainDiskByAliasOrQOM(vm, diskAlias, NULL)))
        goto cleanup;

    job = qemuBlockJobDiskGetJob(disk);

    if (job && job->synchronous) {

        job->newstate = status;
        VIR_FREE(job->errmsg);
        job->errmsg = g_strdup(error);
        virDomainObjBroadcast(vm);
    } else {

        processEvent = g_new0(struct qemuProcessEvent, 1);

        processEvent->eventType = QEMU_PROCESS_EVENT_BLOCK_JOB;
        data = g_strdup(diskAlias);
        processEvent->data = data;
        processEvent->vm = virObjectRef(vm);
        processEvent->action = type;
        processEvent->status = status;

        if (virThreadPoolSendJob(driver->workerPool, 0, processEvent) < 0) {
            virObjectUnref(vm);
            goto cleanup;
        }

        processEvent = NULL;
    }

 cleanup:
    qemuProcessEventFree(processEvent);
    virObjectUnlock(vm);
    return 0;
}
