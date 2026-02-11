userprint() {
    int ix;
    printser(pullp(PSTR("UserSet: (default) ")));
    for (ix = 0; ix < 8; ix++) {
        sprintf(serbuf, pullp(PSTR("%c")), (respget[5] >> ix) & 1 ? userset[ix] : '_');
        printser(serbuf);
    }
    for (ix = 0; ix < 8; ix++) {
        sprintf(serbuf, pullp(PSTR("%c")), (respget[6] >> ix) & 1 ? userset[ix + 8] : '_');
        printser(serbuf);
    }
    for (ix = 0; ix < 8; ix++) {
        sprintf(serbuf, pullp(PSTR("%c")), (respget[7] >> ix) & 1 ? userset[ix + 16] : '_');
        printser(serbuf);
    }
    printser(pullp(PSTR("\r\nUserSet: (changed) ")));
    for (ix = 0; ix < 8; ix++) {
        sprintf(serbuf, pullp(PSTR("%c")), (respget[5] >> ix) & 1 ? '_' : userset[ix]);
        printser(serbuf);
    }
    for (ix = 0; ix < 8; ix++) {
        sprintf(serbuf, pullp(PSTR("%c")), (respget[6] >> ix) & 1 ? '_' : userset[ix + 8]);
        printser(serbuf);
    }
    for (ix = 0; ix < 8; ix++) {
        sprintf(serbuf, pullp(PSTR("%c")), (respget[7] >> ix) & 1 ? '_' : userset[ix + 16]);
        printser(serbuf);
    }
    printser(pullp(PSTR("\r\n")));
}
