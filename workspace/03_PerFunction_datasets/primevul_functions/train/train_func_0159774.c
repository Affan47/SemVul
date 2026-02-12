static void rtl8139_RxBufPtr_write(RTL8139State *s, uint32_t val)
{
    DPRINTF("RxBufPtr write val=0x%04x\n", val);


    s->RxBufPtr = MOD2(val + 0x10, s->RxBufferSize);


    qemu_flush_queued_packets(qemu_get_queue(s->nic));

    DPRINTF(" CAPR write: rx buffer length %d head 0x%04x read 0x%04x\n",
        s->RxBufferSize, s->RxBufAddr, s->RxBufPtr);
}
