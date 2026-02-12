static void scsi_cd_change_media_cb(void *opaque, bool load, Error **errp)
{
    SCSIDiskState *s = opaque;


    s->media_changed = load;
    s->tray_open = !load;
    scsi_device_set_ua(&s->qdev, SENSE_CODE(UNIT_ATTENTION_NO_MEDIUM));
    s->media_event = true;
    s->eject_request = false;
}
