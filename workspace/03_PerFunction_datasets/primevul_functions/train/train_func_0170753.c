static FDrive *get_cur_drv(FDCtrl *fdctrl)
{
    FDrive *cur_drv = get_drv(fdctrl, fdctrl->cur_drv);

    if (!cur_drv->blk) {


        cur_drv->blk = blk_create_empty_drive();
    }
    return cur_drv;
}
