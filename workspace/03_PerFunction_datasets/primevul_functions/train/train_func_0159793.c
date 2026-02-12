static uint32_t rtl8139_RxBufPtr_read(RTL8139State *s)
{

    uint32_t ret = s->RxBufPtr - 0x10;

    DPRINTF("RxBufPtr read val=0x%04x\n", ret);

    return ret;
}
