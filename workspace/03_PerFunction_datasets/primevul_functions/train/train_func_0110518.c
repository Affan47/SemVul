iscsi_abort_task_cb(struct iscsi_context *iscsi, int status, void *command_data,
                    void *private_data)
{
    IscsiAIOCB *acb = private_data;


    if (!acb->bh) {

        iscsi_scsi_cancel_task(iscsi, acb->task);
    }

    qemu_aio_unref(acb);
}
