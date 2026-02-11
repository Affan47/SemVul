func_1_z__region(glui32 argc, glui32 *argv)
{
    glui32 addr;
    glui32 tb;

    if (argc < 1)
        return 0;

    addr = ARG(argv, argc, 0);
    if (addr < 36)
        return 0;
    if (addr >= gEndMem)
        return 0;

    tb = memRead8(addr);
    if (tb >= 0xE0) {
        return 3;
    }
    if (tb >= 0xC0) {
        return 2;
    }
    if (tb >= 0x70 && tb <= 0x7F && addr >= gRamStart) {
        return 1;
    }
    return 0;
}
