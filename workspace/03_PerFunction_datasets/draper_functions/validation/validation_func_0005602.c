main_signal_proc(void)
{
    int i;
    uint32_t sigflag;

    for (i = 0; i < NELEMS(SignalTable); i++) {
        sigflag = 1 << SignalTable[i].sig_no;
        if (SignalReceived & sigflag) {
            SignalReceived &= ~sigflag;
            SignalTable[i].sig_func();
        }
    }
}
