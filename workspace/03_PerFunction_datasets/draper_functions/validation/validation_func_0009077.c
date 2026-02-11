dump_row_ppm(int w, byte **data, FILE *dump_file)
{
    byte *r = data[0];
    byte *g = data[1];
    byte *b = data[2];

    if (dump_file == NULL)
        return;
    while (w--) {
        fputc(*r++, dump_file);
        fputc(*g++, dump_file);
        fputc(*b++, dump_file);
    }
}
