ioc_lockdrv(void __user *arg)
{
    gdth_ioctl_lockdrv ldrv;
    u8 i, j;
    unsigned long flags;
    gdth_ha_str *ha;

    if (copy_from_user(&ldrv, arg, sizeof(gdth_ioctl_lockdrv)))
        return -EFAULT;
    ha = gdth_find_ha(ldrv.ionode);
    if (!ha)
        return -EFAULT;

    for (i = 0; i < ldrv.drive_cnt && i < MAX_HDRIVES; ++i) {
        j = ldrv.drives[i];
        if (j >= MAX_HDRIVES || !ha->hdr[j].present)
            continue;
        if (ldrv.lock) {
            spin_lock_irqsave(&ha->smp_lock, flags);
            ha->hdr[j].lock = 1;
            spin_unlock_irqrestore(&ha->smp_lock, flags);
            gdth_wait_completion(ha, ha->bus_cnt, j);
        } else {
            spin_lock_irqsave(&ha->smp_lock, flags);
            ha->hdr[j].lock = 0;
            spin_unlock_irqrestore(&ha->smp_lock, flags);
            gdth_next(ha);
        }
    }
    return 0;
}
