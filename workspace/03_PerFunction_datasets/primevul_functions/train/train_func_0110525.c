iscsi_aio_cancel(BlockAIOCB *blockacb)
{
    IscsiAIOCB *acb = (IscsiAIOCB *)blockacb;
    IscsiLun *iscsilun = acb->iscsilun;

    qemu_mutex_lock(&iscsilun->mutex);


    if (acb->cancelled || acb->status != -EINPROGRESS) {
        qemu_mutex_unlock(&iscsilun->mutex);
        return;
    }

    acb->cancelled = true;

    qemu_aio_ref(acb);


    if (iscsi_task_mgmt_abort_task_async(iscsilun->iscsi, acb->task,
                                         iscsi_abort_task_cb, acb) < 0) {
        qemu_aio_unref(acb);
    }

    qemu_mutex_unlock(&iscsilun->mutex);
}
