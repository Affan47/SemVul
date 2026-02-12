static int dp8393x_receive_filter(dp8393xState *s, const uint8_t * buf,
                                  int size)
{
    static const uint8_t bcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    int i;


    if ((s->regs[SONIC_RCR] & SONIC_RCR_PRO) && (buf[0] & 1) == 0) {
        return 0;
    }


    if ((s->regs[SONIC_RCR] & SONIC_RCR_AMC) && (buf[0] & 1) == 1) {
        return SONIC_RCR_MC;
    }


    if ((s->regs[SONIC_RCR] & SONIC_RCR_BRD) && !memcmp(buf, bcast, sizeof(bcast))) {
        return SONIC_RCR_BC;
    }


    for (i = 0; i < 16; i++) {
        if (s->regs[SONIC_CE] & (1 << i)) {

             if (!memcmp(buf, s->cam[i], sizeof(s->cam[i]))) {
                 return 0;
             }
        }
    }

    return -1;
}
