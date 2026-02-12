static void test_relative_seek(void)
{
    uint8_t drive = 0;
    uint8_t head = 0;
    uint8_t cyl = 1;
    uint8_t pcn;


    send_seek(0);


    floppy_send(CMD_RELATIVE_SEEK_IN);
    floppy_send(head << 2 | drive);
    g_assert(!get_irq(FLOPPY_IRQ));
    floppy_send(cyl);

    ack_irq(&pcn);
    g_assert(pcn == 1);


    floppy_send(CMD_RELATIVE_SEEK_OUT);
    floppy_send(head << 2 | drive);
    g_assert(!get_irq(FLOPPY_IRQ));
    floppy_send(cyl);

    ack_irq(&pcn);
    g_assert(pcn == 0);
}
