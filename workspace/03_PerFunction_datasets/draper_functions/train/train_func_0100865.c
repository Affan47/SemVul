WriteFloat(const float r, FILE * output)
{

    int j;
    unsigned char *pc;

    pc = (unsigned char *) &r;

    for (j = 0; j < 4; ++j)
        putc(*(pc++), output);

}
