SendNibble(int x) {
        int timeout=TMOUT,retval;

        Out32(LPT1,(x&0x0f)|0x10);

        while (timeout && Inp32(LPT1+1)&8) timeout--;

        retval=(Inp32(LPT1+1)&(0xf0^0x80))>>4;

        Out32(LPT1,0);

        timeout=TMOUT;
        while (timeout && Inp32(LPT1+1)&8) timeout--;

        if (!timeout) { return 0;}
        else return retval;
}
