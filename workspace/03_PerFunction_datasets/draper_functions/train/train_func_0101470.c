set_pin(PROGRAMMER * pgm, int pinname, int val) {
    unsigned char buf[1];

    if (pgm->pin[pinname].mask[0] == 0) {

        return 0;
    }

    ft245r_out = SET_BITS_0(ft245r_out,pgm,pinname,val);
    buf[0] = ft245r_out;

    ft245r_send (pgm, buf, 1);
    ft245r_recv (pgm, buf, 1);

    ft245r_in = buf[0];
    return 0;
}
