static void trim_aio_cancel(BlockDriverAIOCB *acb)
{
    TrimAIOCB *iocb = container_of(acb, TrimAIOCB, common);


    iocb->j = iocb->qiov->niov - 1;
    iocb->i = (iocb->qiov->iov[iocb->j].iov_len / 8) - 1;


    qemu_bh_delete(iocb->bh);
    iocb->bh = NULL;

    if (iocb->aiocb) {
        bdrv_aio_cancel(iocb->aiocb);
    }
    qemu_aio_release(iocb);
}
