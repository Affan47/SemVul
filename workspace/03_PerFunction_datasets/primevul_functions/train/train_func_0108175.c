static void nvme_dsm_cancel(BlockAIOCB *aiocb)
{
    NvmeDSMAIOCB *iocb = container_of(aiocb, NvmeDSMAIOCB, common);


    iocb->idx = iocb->nr;
    iocb->ret = -ECANCELED;

    if (iocb->aiocb) {
        blk_aio_cancel_async(iocb->aiocb);
        iocb->aiocb = NULL;
    } else {


        assert(iocb->idx == iocb->nr);
    }
}
