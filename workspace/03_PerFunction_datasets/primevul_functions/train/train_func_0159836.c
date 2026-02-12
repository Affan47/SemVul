static void rtl8139_transmit(RTL8139State *s)
{
    int descriptor = s->currTxDesc, txcount = 0;


    if (rtl8139_transmit_one(s, descriptor))
    {
        ++s->currTxDesc;
        s->currTxDesc %= 4;
        ++txcount;
    }


    if (!txcount)
    {
        DPRINTF("transmitter queue stalled, current TxDesc = %d\n",
            s->currTxDesc);
    }
}
