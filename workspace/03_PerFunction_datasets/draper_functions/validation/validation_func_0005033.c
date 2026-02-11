Read24BitsHighLow(FILE * fp)
{
    int     first, second, third;
    int     result;

    first = 0xff & getc(fp);
    second = 0xff & getc(fp);
    third = 0xff & getc(fp);

    result = (first << 16) + (second << 8) + third;
    if (result & 0x800000)
        result = result - 0x1000000;
    return (result);
}
