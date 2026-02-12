static void fdctrl_result_timer(void *opaque)
{
    FDCtrl *fdctrl = opaque;
    FDrive *cur_drv = get_cur_drv(fdctrl);


    if (cur_drv->last_sect != 0) {
        cur_drv->sect = (cur_drv->sect % cur_drv->last_sect) + 1;
    }

    if ((fdctrl->dsr & FD_DSR_DRATEMASK) != cur_drv->media_rate) {
        FLOPPY_DPRINTF("read id rate mismatch (fdc=%d, media=%d)\n",
                       fdctrl->dsr & FD_DSR_DRATEMASK, cur_drv->media_rate);
        fdctrl_stop_transfer(fdctrl, FD_SR0_ABNTERM, FD_SR1_MA, 0x00);
    } else {
        fdctrl_stop_transfer(fdctrl, 0x00, 0x00, 0x00);
    }
}
