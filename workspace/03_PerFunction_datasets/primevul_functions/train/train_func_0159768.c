static uint32_t rtl8139_RxBufAddr_read(RTL8139State *s)
{

    uint32_t ret = s->RxBufAddr;

    DPRINTF("RxBufAddr read val=0x%04x\n", ret);

    return ret;
}
