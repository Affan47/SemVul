static void scsi_disk_resize_cb(void *opaque)
{
    SCSIDiskState *s = opaque;


    if (s->qdev.type == TYPE_DISK) {
        scsi_device_report_change(&s->qdev, SENSE_CODE(CAPACITY_CHANGED));
    }
}
